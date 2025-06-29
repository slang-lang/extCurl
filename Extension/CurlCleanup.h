
#ifndef Extensions_Curl_CurlCleanup_h
#define Extensions_Curl_CurlCleanup_h


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


class CurlCleanup: public Extensions::ExtensionMethod
{
public:
	CurlCleanup()
	: ExtensionMethod(0, "curl_cleanup", Designtime::VoidType::TYPENAME, Mutability::Modify)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("handle", Designtime::Int32Type::TYPENAME));

		setSignature(params);
	}


	Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* /*result*/ )
	{
		auto it = params.cbegin();
		auto paramHandle = (*it++).value().toInt();

		if ( paramHandle > 0 && paramHandle < static_cast<int>( Requests.size() ) ) {
			auto& request = Requests[paramHandle];

			curl_easy_cleanup( request->Handle );

			request->Handle = nullptr;
			request->Result.clear();
		}

		return Runtime::ControlFlow::Normal;
	}
};


}


#endif
