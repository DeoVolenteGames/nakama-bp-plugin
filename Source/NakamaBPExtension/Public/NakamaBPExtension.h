// Copyright 2021 DeoVolenteGames

#pragma once

#include "Modules/ModuleManager.h"
#include "NakamaUnreal.h"
#include "nonstd/optional.hpp"
#include <Tickable.h>
// #include "NakamaError.h"

DECLARE_LOG_CATEGORY_EXTERN(LogNakamaBPExtension, Log, All);

// using namespace NAKAMA_NAMESPACE;
using nonstd::optional;
using nonstd::nullopt;

// TODO: Add global error default, see https://heroiclabs.github.io/nakama-cpp/html/class_n_client_interface.html#a283932460c8ea2d1a603667da52c565b
// DECLARE_DYNAMIC_DELEGATE_OneParam(FErrorDelegate, const FString)

class NAKAMABPEXTENSION_API FNakamaBPExtensionModule : public FTickableGameObject, public IModuleInterface
{
public:
	// FNakamaBPExtensionModule();

	// DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAnyNakamaErrorResponse, FNakamaErrorResponse, ErrorResponse);
	
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	/** FTickableGameObject implementation */
	virtual TStatId GetStatId() const override
	{ RETURN_QUICK_DECLARE_CYCLE_STAT(FNakamaBPExtensionModule, STATGROUP_Tickables); };
	virtual bool IsTickable() const override { return true; };
	virtual bool IsTickableInEditor() const override { return false; };
	virtual bool IsTickableWhenPaused() const override { return true; };
	virtual void Tick(float DeltaTime) override;

	static NAKAMA_NAMESPACE::NClientPtr Client;
	static NAKAMA_NAMESPACE::NRtClientPtr RtClient;
	// static NAKAMA_NAMESPACE::NRtDefaultClientListener RtListener;
	static NAKAMA_NAMESPACE::NSessionPtr Session;
	// static FOnAnyNakamaErrorResponse DefaultErrorCallback;
	
	// I have a baaaad feeling about this...
	template<typename ArrayType, typename VectorType>
    static TArray<ArrayType> MakeArray(const VectorType& Vector)
	{
		TArray<ArrayType> Array;
		Array.SetNumUninitialized(Vector.size());
 
		for(int i=0; i< Vector.size(); i++){
			Array[i] = Vector[i];
		}

		return Array;
	}
	// // I have a baaaad feeling about this...
	// template<typename VectorType, typename ArrayType>
 //    static VectorType MakeVec(const ArrayType& Array)
	// {
	// 	VectorType Vector;
	// 	for (auto ID : Array)
	// 	{
	// 		Vector.push_back(ID.ToNReadStorageObjectId());
	// 	}
 //
	// 	return Vector;
	// }
};

using NakamaBP = FNakamaBPExtensionModule;
