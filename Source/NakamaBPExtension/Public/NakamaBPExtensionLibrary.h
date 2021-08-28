// Copyright 2021 DeoVolenteGames

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "NakamaUnreal.h"
#include "NakamaBPExtensionLibrary.generated.h"

using namespace NAKAMA_NAMESPACE;

/*
* 
*/
UCLASS()
class NAKAMABPEXTENSION_API UNakamaBPExtensionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	// Create client call from docs. Optional, will use default values if not called.
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Create Nakama Client", Keywords = "Connect, Init, Setup", AdvancedDisplay = "0"), Category = "Nakama BP Extension")
		static void CreateClient(const FString ServerKey, const FString Host, const int Port = -1);

	// TODO: Return session struct
	UFUNCTION(BlueprintPure, Category = "Nakama BP Extension")
	static bool GetSessionKey(FString& Token);
	
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Disconnect Nakama Client"), Category = "Nakama BP Extension")
        static void DisconnectClient();
};
