#ifndef __PAGE_BASE_H
#define __PAGE_BASE_H

#include "lvgl.h"

#define PAGE_STASH_MAKE(data)   {&(data), sizeof(data)}

#define PAGE_STASH_POP(data)    this->GetStash(&(data), sizeof(data))

class PageManager;

class PageBase
{
public:
    typedef enum
    {
        PAGE_STATE_IDLE,
        PAGE_STATE_LOAD,
        PAGE_STATE_WILL_APPEAR,
        PAGE_STATE_DID_APPEAR,
        PAGE_STATE_ACTIVITY,
        PAGE_STATE_WILL_DISAPPEAR,
        PAGE_STATE_DID_DISAPPERA,
        PAGE_STATE_UNLOAD,
        _PAGE_STATE_LAST
    } State_t;

    typedef struct 
    {
        void *ptr;
        uint32_t size;
    } Stash_t;

    typedef struct
    {
        uint8_t Type;
        uint16_t Time;
        lv_anim_path_cb_t Path;
    } AnimAttr_t;

public:
    lv_obj_t *root;
    PageManager* Manager;
    const char *Name;
    uint16_t ID;
    void *UserData;

    struct 
    {
        bool ReqEnableCache;
        bool ReqDisableAutoCache;
        bool IsDisableAutoCache;
        bool IsCached;
        Stash_t Stash;
        State_t State;

        struct 
        {
            bool IsEnter;
            bool IsBusy;
            AnimAttr_t Attr;
        } Anim;
    } priv;

public:
    virtual ~PageBase() {}
    virtual void onCustomAttrConfig() {}
    virtual void OnViewLoad() {}
    virtual void onViewDiaLoad() {}
    virtual void onViewWillAppear() {}
    virtual void onViewDidAppear() {}
    virtual void onViewWillDisappear() {}
    virtual void onViewDidDisappear() {}
    virtual void onViewDidUnload() {}
    void SetCustomCacheEnable(bool en)
    {
        priv.ReqDisableAutoCache = !en;
    }

    void SetCustomLoadAnimType(
        uint8_t animType,
        uint16_t time = 500,
        lv_anim_path_cb_t path = lv_anim_path_ease_out
    )
    {
        priv.Anim.Attr.Type = animType;
        priv.Anim.Attr.Time = time;
        priv.Anim.Attr.Path = path;
    }

    bool GetStash(void *ptr, uint32_t size)
    {
        bool retval = false;
        if (priv.Stash.ptr != nullptr && priv.Stash.size == size)
        {
            memcpy(ptr, priv.Stash.ptr, priv.Stash.size);
            retval = true;
        }
        return retval;
    }
};

#endif