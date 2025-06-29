
#ifndef Extensions_Curl_CurlInit_h
#define Extensions_Curl_CurlInit_h


// Library include

// Project includes
#include <Core/Designtime/BuildInTypes/Int32Type.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/Int32Type.h>
#include <Core/Runtime/BuildInTypes/StringType.h>
#include "Types.h"

// Forward declarations

// Namespace declarations
using namespace Slang;


namespace Curl {


class CurlInit: public Extensions::ExtensionMethod
{
public:
	CurlInit()
	: ExtensionMethod(0, "curl_init", Designtime::Int32Type::TYPENAME, Mutability::Modify)
	{
		ParameterList params;

		setSignature(params);
	}


	Runtime::ControlFlow::E execute( const ParameterList& /*params*/, Runtime::Object* result )
	{
		// duplicate base handle, since we want to inherit all of its already set options
		//CURL* newHandle = curl_easy_duphandle( Requests[0].Handle );
		auto* newHandle = curl_easy_init();

		int32_t methodResult = 0;
		if ( newHandle ) {
			auto* request = new CurlRequest();
			request->Handle = newHandle;

			curl_easy_setopt( newHandle, CURLOPT_WRITEFUNCTION, Extension::write_data );

			methodResult = static_cast<int32_t>( Requests.size() );

			Requests.insert( std::make_pair( Requests.size(), request ) );
		}

		*result = Runtime::Int32Type( methodResult );

		return Runtime::ControlFlow::Normal;
	}
};


}


#endif
