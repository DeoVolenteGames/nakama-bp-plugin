// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "NakamaBPExtension.h"
#include "NUnrealLogSink.h"

#define LOCTEXT_NAMESPACE "FNakamaBPExtensionModule"

DEFINE_LOG_CATEGORY(LogNakamaBPExtension);

NAKAMA_NAMESPACE::NClientPtr FNakamaBPExtensionModule::Client;
NAKAMA_NAMESPACE::NSessionPtr FNakamaBPExtensionModule::Session;

// FNakamaBPExtensionModule::FNakamaBPExtensionModule()
// {
// 	
// }

void FNakamaBPExtensionModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	NAKAMA_NAMESPACE::NLogger::init(std::make_shared<NAKAMA_NAMESPACE::NUnrealLogSink>(), NAKAMA_NAMESPACE::NLogLevel::Debug);

	// TODO: Read client default parameters from config file (ini).
	NakamaBP::Client = NAKAMA_NAMESPACE::createDefaultClient(NAKAMA_NAMESPACE::NClientParameters());

	 // TODO: Restore session: https://github.com/heroiclabs/nakama-cpp/blob/master/examples/nakama-cmake-client-example/nakama-cmake-client-example.cpp#L47
}

void FNakamaBPExtensionModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

void FNakamaBPExtensionModule::Tick(float DeltaTime)
{
	// Tick client to see if async functions have completed.
	if (Client) Client->tick();
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FNakamaBPExtensionModule, NakamaBPExtension)

#include "nakama-cpp-c-wrapper/NakamaWrapperImpl.h"
