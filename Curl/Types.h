
#ifndef Extensions_Curl_Types_h
#define Extensions_Curl_Types_h


// Library includes
#include <curl/curl.h>
#include <map>
#include <string>

// Project includes
#include <Core/Common/Exceptions.h>
//#include <Core/Designtime/BuildInTypes/BoolObject.h>
//#include <Core/Designtime/BuildInTypes/IntegerObject.h>
//#include <Core/Designtime/BuildInTypes/StringObject.h>
//#include <Core/Designtime/BuildInTypes/VoidObject.h>
#include <Core/Extensions/ExtensionMethod.h>
//#include <Core/Runtime/BuildInTypes/IntegerObject.h>
//#include <Core/Runtime/BuildInTypes/StringObject.h>
#include <Core/VirtualMachine/Controller.h>
#include <Core/Tools.h>

// Forward declarations

// Namespace declarations


namespace Curl {


struct CurlRequest {
	CURL*		Handle { nullptr };
	std::string	Header;
	struct curl_slist* HeaderList { nullptr };
	std::string	Result;

	~CurlRequest() {
		// free the list again
		curl_slist_free_all( HeaderList );
	}
};


typedef std::map<size_t, CurlRequest*> CurlRequests;

extern CurlRequests Requests;

void cleanup();
void init();


}


#endif

