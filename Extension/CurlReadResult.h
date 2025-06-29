
#ifndef Extensions_Curl_CurlReadResult_h
#define Extensions_Curl_CurlReadResult_h


// Library include

// Project includes
#include <Core/Designtime/BuildInTypes/Int32Type.h>
#include <Core/Designtime/BuildInTypes/StringType.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/Int32Type.h>
#include <Core/Runtime/BuildInTypes/StringType.h>
#include "Types.h"

// Forward declarations

// Namespace declarations
using namespace Slang;


namespace Curl {


class CurlReadResult: public Extensions::ExtensionMethod
{
public:
	CurlReadResult()
	: ExtensionMethod(0, "curl_read_result", Designtime::StringType::TYPENAME, Mutability::Modify)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("handle", Designtime::Int32Type::TYPENAME));

		setSignature(params);
	}


	Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* result )
	{
		auto it = params.cbegin();
		auto paramHandle = (*it++).value().toInt();

		if ( paramHandle > 0 && paramHandle < static_cast<int32_t>( Requests.size() ) ) {
			auto request = Requests[paramHandle];

			*result = Runtime::StringType( request->Result );
		}

		return Runtime::ControlFlow::Normal;
	}
};


}


#endif
