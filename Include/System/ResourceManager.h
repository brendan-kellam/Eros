#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#pragma once

#include "Util/Helpers/ManagerHelper.h"

EXTERN_C IMAGE_DOS_HEADER __ImageBase;


class EROS_API CResourceManager final 
	: NEWMANAGER(CResourceManager)
{

public:

	void StartUp()  override;
	void ShutDown() override;

	
	std::string GetBaseProjectPath();
	std::string GetBaseResourcePath();

	std::string GetResourcePath(std::string extension);
	std::string GetShaderPath(std::string name);

private:

	std::string m_projectPath;


};



#endif /* RESOURCEMANAGER_H */
