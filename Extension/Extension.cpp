
// Header
#include "Extension.h"

// Library includes
#include <cassert>

// Project includes
#include "CurlCleanup.h"
#include "CurlInit.h"
#include "CurlPerform.h"
#include "CurlReadResult.h"
#include "CurlReset.h"
#include "CurlSetBearer.h"
#include "CurlSetData.h"
#include "CurlSetHeader.h"
#include "CurlSetOptInt.h"
#include "CurlSetOptStr.h"
#include "CurlSetPassword.h"
#include "CurlSetProgress.h"
#include "CurlSetUrl.h"
#include "CurlSetUsername.h"
#include "CurlSetVerbose.h"

// Namespace declarations


namespace Curl {


Extension::Extension()
: Slang::Extensions::AExtension( "extCurl", "0.4.0" )
{
	curl_global_init( CURL_GLOBAL_ALL );

	// initialize name & version
	auto* curl = curl_version_info( CURLVERSION_NOW );
	mName      = "extCurl (using libCurl " + std::string( curl->version ) + ")";

	Curl::init();
}

Extension::~Extension()
{
	Curl::cleanup();

	curl_global_cleanup();
}

void Extension::initialize( Slang::Extensions::ExtensionNamespace* scope )
{
	(void)scope;

	// global vars/consts currently don't work for extensions :-(

	//scope->define( "CURLOPT_XOAUTH2_BEARER", new Slang::Runtime::Int32Type( "CURLOPT_XOAUTH2_BEARER", CURLOPT_XOAUTH2_BEARER ) );
}

void Extension::provideMethods( Slang::Extensions::ExtensionMethods& methods )
{
	assert( methods.empty() );

	methods.push_back( new CurlCleanup() );
	methods.push_back( new CurlInit() );
	methods.push_back( new CurlPerform() );
	methods.push_back( new CurlReadResult() );
	methods.push_back( new CurlReset() );
	methods.push_back( new CurlSetBearer() );
	methods.push_back( new CurlSetData() );
	methods.push_back( new CurlSetHeader() );
	methods.push_back( new CurlSetOptInt() );
	methods.push_back( new CurlSetOptStr() );
	methods.push_back( new CurlSetPassword() );
	methods.push_back( new CurlSetProgress() );
	methods.push_back( new CurlSetUrl() );
	methods.push_back( new CurlSetUsername() );
	methods.push_back( new CurlSetVerbose() );
}

size_t Extension::write_data( void *contents, size_t size, size_t nmemb, void *stream )
{
	static_cast<std::string*>( stream )->append( (char*)contents, size * nmemb );

	return size * nmemb;
}


}


extern "C" Slang::Extensions::AExtension* factory( void ) {
	return dynamic_cast<Slang::Extensions::AExtension*>( new Curl::Extension() );
}
