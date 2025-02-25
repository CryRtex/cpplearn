#include "Core.h"
#include <iostream>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

namespace Core {

	void printjson()
	{
		rapidjson::Document document;
		document.SetObject();

		rapidjson::Document::AllocatorType& allocator = document.GetAllocator(); // Bellk tahsis edici özelliktir //
		rapidjson::Value object(rapidjson::kObjectType);

		object.AddMember("name", "John Doe", allocator);
		object.AddMember("age", 25, allocator);

		document.AddMember("person", object, allocator);
		rapidjson::StringBuffer strbuf;

		rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
		document.Accept(writer);

		std::cout << strbuf.GetString() << std::endl;
	
	}

}
