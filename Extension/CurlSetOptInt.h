
#ifndef Extensions_Curl_CurlSetOptInt_h
#define Extensions_Curl_CurlSetOptInt_h


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


class CurlSetOptInt : public Extensions::ExtensionMethod
{
public:
	CurlSetOptInt()
	: ExtensionMethod(0, "curl_set_opt_int", Designtime::VoidType::TYPENAME, Mutability::Modify)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("handle", Designtime::Int32Type::TYPENAME));
		params.push_back(Parameter::CreateDesigntime("option", Designtime::Int32Type::TYPENAME));
		params.push_back(Parameter::CreateDesigntime("value", Designtime::Int32Type::TYPENAME));

		setSignature(params);
	}


	Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* /*result*/ )
	{
		auto it = params.cbegin();
		auto paramHandle = (*it++).value().toInt();
		auto paramOption = (*it++).value().toInt();
		auto paramValue = (*it++).value().toInt();

		if ( paramHandle > 0 && paramHandle < static_cast<int32_t>( Requests.size() ) ) {
			auto& request = Requests[paramHandle];

			curl_easy_setopt( request->Handle, static_cast<CURLoption>( paramOption ), paramValue );
		}

		return Runtime::ControlFlow::Normal;
	}
};


}


#endif
