
#ifndef Extensions_Curl_CurlSetProgress_h
#define Extensions_Curl_CurlSetProgress_h


// Library include

// Project includes
#include <Core/Designtime/BuildInTypes/BoolType.h>
#include <Core/Designtime/BuildInTypes/Int32Type.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/Int32Type.h>
#include <Core/Runtime/BuildInTypes/StringType.h>
#include "Types.h"

// Forward declarations

// Namespace declarations
using namespace Slang;


namespace Curl {


class CurlSetProgress: public Extensions::ExtensionMethod
{
public:
	CurlSetProgress()
	: ExtensionMethod(0, "curl_set_progress", Designtime::VoidType::TYPENAME, Mutability::Modify)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("handle", Designtime::Int32Type::TYPENAME));
		params.push_back(Parameter::CreateDesigntime("progress", Designtime::BoolType::TYPENAME));

		setSignature(params);
	}


	Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* /*result*/ )
	{
		auto it = params.cbegin();
		auto paramHandle = (*it++).value().toInt();
		auto paramProgress = (*it++).value().toBool();

		if ( paramHandle > 0 && paramHandle < static_cast<int32_t>( Requests.size() ) ) {
			auto& request = Requests[paramHandle];

			curl_easy_setopt( request->Handle, CURLOPT_NOPROGRESS, !paramProgress );
		}

		return Runtime::ControlFlow::Normal;
	}
};


}


#endif
