
#ifndef Extensions_Curl_CurlSetData_h
#define Extensions_Curl_CurlSetData_h


// Library include

// Project includes
#include <Core/Designtime/BuildInTypes/Int32Type.h>
#include <Core/Designtime/BuildInTypes/StringType.h>
#include <Core/Designtime/BuildInTypes/VoidType.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/Int32Type.h>
#include <Core/Runtime/BuildInTypes/StringType.h>
#include "Types.h"

// Forward declarations

// Namespace declarations
using namespace Slang;


namespace Curl {


class CurlSetData: public Extensions::ExtensionMethod
{
public:
	CurlSetData()
	: ExtensionMethod(0, "curl_set_data", Designtime::VoidType::TYPENAME, Mutability::Modify)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("handle", Designtime::Int32Type::TYPENAME));
		params.push_back(Parameter::CreateDesigntime("data", Designtime::StringType::TYPENAME));

		setSignature(params);
	}

	Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* /*result*/ )
	{
		auto it = params.cbegin();
		auto paramHandle = (*it++).value().toInt();
		auto paramData = (*it++).value().toStdString();

		if ( paramHandle > 0 && paramHandle < static_cast<int32_t>( Requests.size() ) ) {
			auto& request = Requests[paramHandle];

			curl_easy_setopt( request->Handle, CURLOPT_POST, 1L );
			// size of the data to copy from the buffer and send in the request
			curl_easy_setopt( request->Handle, CURLOPT_POSTFIELDSIZE, static_cast<long>( paramData.size() ) );
			// send data from the local stack
			curl_easy_setopt( request->Handle, CURLOPT_COPYPOSTFIELDS, paramData.c_str() );
		}

		return Runtime::ControlFlow::Normal;
	}
};


}


#endif
