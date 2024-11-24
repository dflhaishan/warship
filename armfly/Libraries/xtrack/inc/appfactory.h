#ifndef __APP_FACTORY_H
#define __APP_FACTORY_H

#include "pagemanager.h"

class AppFactory : public PageFactory
{
public:
    virtual PageBase *CreatePage(const char *name);
private:
}

#endif