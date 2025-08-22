//=============================================================================
// _____     ___ ____  # insert another cool logo here
//  ____|   |    ____| # insert another cool logo here
// |     ___|   |____  # insert another cool logo here
// ---------------------------------------------------
//
// File:        filer.cpp
//
// Description: 
//
//=============================================================================

//========================================
// System Includes
//========================================

#include <exception>

/* libc */
#include <unistd.h>

//========================================
// PS2SDK Includes
//========================================

/* libkernel */
#include <kernel.h>
#include <iopcontrol.h>
#include <loadfile.h>

#include <libpad.h>

//========================================
// Project Includes
//========================================

/* sol */
#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>

//========================================
// Definitions
//========================================

/* very ugly hack */
void* __dso_handle;

struct pad {
    int mPort, mSlot;
    struct padButtonStatus mData;
    uint8_t mActAlign[6];
    uint8_t* mBuffer;

    pad(int port, int slot) : mPort(port), mSlot(slot) {
        mBuffer = new(std::align_val_t(64)) uint8_t[256];

        int ret;
        if((ret = padPortOpen(mPort, mSlot, mBuffer)) == 0) {
            printf("pad %d:%d failed to open port: %d\n", mPort, mSlot, ret);
            throw std::runtime_error("failed to open pad port");
        }

        if((ret = sync()) < 0) throw std::runtime_error("failed to sync pad");

        bool hasDualshockMode = false;

        int modes = padInfoMode(mPort, mSlot, PAD_MODETABLE, -1);
        if(modes) {
            for(int i = 0; i < modes; i++) {
                int mode = padInfoMode(mPort, mSlot, PAD_MODETABLE, i);
                if(mode == PAD_TYPE_DUALSHOCK) hasDualshockMode = true;
                printf("pad %d:%d mode[%d]: %d\n", mPort, mSlot, i, mode);
            }
            printf("pad %d:%d current mode: %d\n", mPort, mSlot, padInfoMode(mPort, mSlot, PAD_MODECURID, 0));
        } else {
            printf("pad %d:%d no modes available\n", mPort, mSlot);
            throw std::runtime_error("no modes available");
        }

        if(!hasDualshockMode) throw std::runtime_error("no dualshock mode available");
        if(!padInfoMode(mPort, mSlot, PAD_MODECUREXID, 0)) throw std::runtime_error("not a dualshock 2 controller");

        padSetMainMode(mPort, mSlot, PAD_MMODE_DUALSHOCK, PAD_MMODE_LOCK);
        if((ret = sync()) < 0) throw std::runtime_error("failed to sync pad");

        padInfoPressMode(mPort, mSlot);
        if((ret = sync()) < 0) throw std::runtime_error("failed to sync pad");
        
        padEnterPressMode(mPort, mSlot);
        if((ret = sync()) < 0) throw std::runtime_error("failed to sync pad");

        int actuators = padInfoAct(mPort, mSlot, -1, 0);
        if (actuators != 0) {
            mActAlign[0] = 0;
            mActAlign[1] = 1;
            mActAlign[2] = 0xff;
            mActAlign[3] = 0xff;
            mActAlign[4] = 0xff;
            mActAlign[5] = 0xff;
            padSetActAlign(mPort, mSlot, (const char*) mActAlign);
            if((ret = sync()) < 0) throw std::runtime_error("failed to sync pad");
        }   

    }

    int poll() {
        
        int state = 0;
        while((state = padGetState(mPort, mSlot)) != PAD_STATE_STABLE) {
            if(state == PAD_STATE_DISCONN) {
                return -1;
            }
        }
        padRead(mPort, mSlot, &mData);
        return 0;
    }

    bool isPressed(int button) {
        return (mData.btns & button) == 0;
    }

    float getPressure(int button) {
        switch (button)
        {
            case PAD_UP: return mData.up_p / 255.0f;
            case PAD_DOWN: return mData.down_p / 255.0f;
            case PAD_LEFT: return mData.left_p / 255.0f;
            case PAD_RIGHT: return mData.right_p / 255.0f;
            case PAD_L2: return mData.l2_p / 255.0f;
            case PAD_R2: return mData.r2_p / 255.0f;
            case PAD_L1: return mData.l1_p / 255.0f;
            case PAD_R1: return mData.r1_p / 255.0f;
            case PAD_TRIANGLE: return mData.triangle_p / 255.0f;
            case PAD_CIRCLE: return mData.circle_p / 255.0f;
            case PAD_CROSS: return mData.cross_p / 255.0f;
            case PAD_SQUARE: return mData.square_p / 255.0f;
            default: return 0.0f;
        }
    }

    float getLeftStickX() { return mData.ljoy_h / 127.0f - 1.0F; }

    float getLeftStickY() { return mData.ljoy_v / 127.0f - 1.0F; }

    float getRightStickX() { return mData.rjoy_h / 127.0f - 1.0F; }

    float getRightStickY() { return mData.rjoy_v / 127.0f - 1.0F; }

    int sync() {
        int state = 0, lastState = 0;
        while((state = padGetState(mPort, mSlot)) != PAD_STATE_STABLE) {
            if(state != lastState) {
                char stateString[16];
                padStateInt2String(state, stateString);
                printf("pad %d:%d state: %s\n", mPort, mSlot, stateString);
            }
            switch (state)
            {
                case PAD_STATE_DISCONN: return -1;
            }
            lastState = state;
        }
        return 0;
    }

    ~pad() {
        padPortClose(mPort, mSlot);
        delete[] mBuffer;
    }
};

void load_irx(const char* path, int arglen = 0, const char* args = nullptr) {
    char buf[256];
    getcwd(buf, sizeof(buf));
    sprintf(buf + strlen(buf), "/irx/%s", path);
    int id = SifLoadModule(buf, arglen, args);
    if(id < 0) {
        throw std::runtime_error("failed to load iop module");
    }
}

namespace api {

pad* pad0;

void initialize() {
    load_irx("sio2man.irx");
    load_irx("padman.irx");
    if(padInit(0) != 1) throw std::runtime_error("failed to initialize padman");
    pad0 = new pad(0, 0);
}

pad& getController(int port, int slot) {
    if(port < 0 || port > 3 || slot < 0 || slot > 1) {
        throw std::runtime_error("invalid pad port or slot");
    }
    return *pad0;
}

}

extern "C" __attribute__((visibility("default"))) int luaopen_luainput(lua_State* L) noexcept try {
    sol::state_view lua(L);

    lua.new_usertype<pad>("pad",
        "poll", &pad::poll,
        "isPressed", &pad::isPressed,
        "getPressure", &pad::getPressure,
        "getLeftStickX", &pad::getLeftStickX,
        "getLeftStickY", &pad::getLeftStickY,
        "getRightStickX", &pad::getRightStickX,
        "getRightStickY", &pad::getRightStickY
    );

    auto table = lua.create_table();
    
    table["LEFT"] = PAD_LEFT;
    table["DOWN"] = PAD_DOWN;
    table["RIGHT"] = PAD_RIGHT;
    table["UP"] = PAD_UP;
    table["START"] = PAD_START;
    table["R3"] = PAD_R3;
    table["L3"] = PAD_L3;
    table["SELECT"] = PAD_SELECT;
    table["SQUARE"] = PAD_SQUARE;
    table["CROSS"] = PAD_CROSS;
    table["CIRCLE"] = PAD_CIRCLE;
    table["TRIANGLE"] = PAD_TRIANGLE;
    table["R1"] = PAD_R1;
    table["L1"] = PAD_L1;
    table["R2"] = PAD_R2;
    table["L2"] = PAD_L2;

    table["initialize"] = &api::initialize;
    table["getController"] = &api::getController;

    table.push();

    return 1;
} catch (std::exception& e) {
    return luaL_error(L, "%s", e.what());
}