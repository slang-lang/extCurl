
#ifndef Curl_Extension_h
#define Curl_Extension_h


// Library includes

// Project includes
#include <Core/Extensions/AExtension.h>

// Forward declarations

// Namespace declarations


namespace Curl {


class Extension : public Slang::Extensions::AExtension
{
public:
	Extension();
	~Extension() override;

public:
	void initialize( Slang::Extensions::ExtensionNamespace* scope ) override;
	void provideMethods( Slang::Extensions::ExtensionMethods &methods ) override;

public:
	static size_t write_data( void *contents, size_t size, size_t nmemb, void *stream );
};


}


#endif

