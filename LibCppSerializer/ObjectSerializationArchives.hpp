#pragma once

#include "boost\archive\text_iarchive.hpp"
#include "boost\archive\text_oarchive.hpp"
#include "boost\archive\binary_iarchive.hpp"
#include "boost\archive\binary_oarchive.hpp"
#include <unordered_map>

namespace objserialization
{
	enum class ArchiveType
	{
		BINARY,
		TEXT
	};

	template<typename T>
	class Archive
	{
	private:
		T ar;

	public:
		Archive(std::istringstream iss)
			: _ar(iss)
		{}

		template<typename C>
		void operator>> (C& obj)
		{
			_ar >> obj;
		}
	};
}


