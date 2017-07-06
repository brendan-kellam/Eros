#ifndef MANAGERHELPER_H
#define MANAGERHELPER_H

#pragma once

/* Required includes */
#include "System/Platform.h"
#include "Util/Interfaces/Manager.h"
#include "Util/Singleton.h"

/* Macro for Singleton and Manager interface include */
#define NEWMANAGER(X) public CSingleton< X >, public Interface::IManager

#endif /* MANAGERHELPER_H */
