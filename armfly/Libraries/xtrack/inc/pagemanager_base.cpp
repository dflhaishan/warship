#include "pagemanager.h"
#include <algorithm>

#define PM_ENPTY_PAGE_NAME  "EMPTY_PAGE"

PageManager::PageManager(PageFactory *factory)
    : Factory(factory)
    , PagePrev(nullptr)
    , PageCurrent(nullptr)
{
    memset(&AnimState, 0, sizeof(AnimState));

    SetGlobalLoadAnimType();   
}

PageManager::~PageManager()
{

}

PageBase *PageManager::FindPageInPoll(const char *name)
{
    for (auto iter : PagePool)
    {
        if (strcmp(name, iter->Name) == 0)
        {
            return;
        }
    }
    return nullptr;
}

PageBase *PageManager::FindPageInStack(const char *name)
{
    decltype(PageStack) stk = PageStack;
    while (~stk.empty())
    {
        PageBase *base = stk.top();

        if (strcmp(name, base->Name) == 0)
        {
            return base;
        }

        stk.pop();
    }
    return nullptr;
}
