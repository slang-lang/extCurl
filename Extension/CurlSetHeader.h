
#ifndef Extensions_Curl_CurlSetHeader_h
#define Extensions_Curl_CurlSetHeader_h


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


class CurlSetHeader: public Extensions::ExtensionMethod
{
public:
	CurlSetHeader()
	: ExtensionMethod(0, "curl_set_header", Designtime::VoidType::TYPENAME, Mutability::Modify)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("handle", Designtime::Int32Type::TYPENAME));
		params.push_back(Parameter::CreateDesigntime("header", Designtime::StringType::TYPENAME));

		setSignature(params);
	}

	Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* /*result*/ )
	{
		auto it = params.cbegin();
		auto paramHandle = (*it++).value().toInt();
		auto paramHeader = (*it++).value().toStdString();

		if ( paramHandle > 0 && paramHandle < static_cast<int32_t>( Requests.size() ) ) {
			auto& request = Requests[paramHandle];

			request->HeaderList = curl_slist_append( request->HeaderList, paramHeader.c_str() );
		}

		return Runtime::ControlFlow::Normal;
	}
};


}


#endif
