#ifndef NONCOPYABLEINTERFACE_H
#define NONCOPYABLEINTERFACE_H

#pragma once

#include "System/Platform.h"

namespace Interface
{

	class EROS_API INonCopyable
	{
	protected:
		INonCopyable()
		{ }

		~INonCopyable()
		{ }

	private:
		INonCopyable(const INonCopyable& other) = delete;
		const INonCopyable& operator= (const INonCopyable& other) = delete;
	};

}

#endif
