
#ifndef Extensions_Curl_CurlPerform_h
#define Extensions_Curl_CurlPerform_h


// Library include

// Project includes
#include <Core/Designtime/BuildInTypes/Int32Type.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/Int32Type.h>
#include <Core/Runtime/BuildInTypes/StringType.h>
#include <Core/Tools.h>
#include "Types.h"

// Forward declarations

// Namespace declarations
using namespace Slang;


namespace Curl {


class CurlPerform: public Extensions::ExtensionMethod
{
public:
	CurlPerform()
	: ExtensionMethod(0, "curl_perform", Designtime::Int32Type::TYPENAME, Mutability::Modify)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("handle", Designtime::Int32Type::TYPENAME));

		setSignature(params);
	}


	Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* result )
	{
		auto it = params.cbegin();
		auto paramHandle = (*it++).value().toInt();

		int32_t methodResult = 0;
		if ( paramHandle > 0 && paramHandle < static_cast<int32_t>( Requests.size() ) ) {
			auto& request = Requests[paramHandle];

			curl_easy_setopt( request->Handle, CURLOPT_HTTPHEADER, request->HeaderList );
			curl_easy_setopt( request->Handle, CURLOPT_WRITEDATA, &request->Result );

			methodResult = curl_easy_perform( request->Handle );
		}

		*result = Runtime::Int32Type( methodResult );

		return Runtime::ControlFlow::Normal;
	}
};


}


#endif
