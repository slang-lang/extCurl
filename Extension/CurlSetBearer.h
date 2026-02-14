
#ifndef Extensions_Curl_CurlSetBearer_h
#define Extensions_Curl_CurlSetBearer_h


// Library include

// Project includes
#include <Core/Designtime/BuildInTypes/Int32Type.h>
#include <Core/Designtime/BuildInTypes/VoidType.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/Int32Type.h>
#include <Core/Runtime/BuildInTypes/StringType.h>
#include "Types.h"

// Forward declarations

// Namespace declarations
using namespace Slang;


namespace Curl {


class CurlSetBearer: public Extensions::ExtensionMethod
{
public:
	CurlSetBearer()
	: ExtensionMethod(0, "curl_set_bearer", Designtime::VoidType::TYPENAME, Mutability::Modify)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("handle", Designtime::Int32Type::TYPENAME));
		params.push_back(Parameter::CreateDesigntime("bearer", Designtime::StringType::TYPENAME));

		setSignature(params);
	}

	Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* /*result*/ )
	{
		auto it = params.cbegin();
		auto paramHandle = (*it++).value().toInt();
		auto paramBearer = (*it++).value().toStdString();

		if ( paramHandle > 0 && paramHandle < static_cast<int32_t>( Requests.size() ) ) {
			auto& request = Requests[paramHandle];

			curl_easy_setopt( request->Handle, CURLOPT_XOAUTH2_BEARER, paramBearer.c_str() );
#ifdef CURLAUTH_BEARER
			curl_easy_setopt( request->Handle, CURLOPT_HTTPAUTH, CURLAUTH_BEARER );
#else
			curl_easy_setopt( request->Handle, CURLOPT_HTTPAUTH, CURLAUTH_ANY );
#endif
		}

		return Runtime::ControlFlow::Normal;
	}
};


}


#endif
