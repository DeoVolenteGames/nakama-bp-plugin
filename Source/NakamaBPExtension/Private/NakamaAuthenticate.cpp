// Fill out your copyright notice in the Description page of Project Settings.

#include "..\Public\NakamaAuthenticate.h"
#include "NakamaBPExtension.h"

// https://wiki.unrealengine.com/Creating_Asynchronous_Blueprint_Nodes

void UNakamaAuthenticate::Activate()
{
	// TODO: Use FFrame::KismetExecutionMessage for logging errors?
	if (!NakamaBP::Client)
	{
		BroadcastError(OnError, TEXT("Client session not connected"));
		return;
	}

	auto Success = [&, this](NAKAMA_NAMESPACE::NSessionPtr NewSession) 
	{
		NakamaBP::Session = NewSession; BroadcastSuccess(OnSuccess, FNakamaAuthenticateSessionResponse(NewSession));
	};
	auto Error = [&, this](const NAKAMA_NAMESPACE::NError& Error) { BroadcastError(OnError, Error); };

	switch (AuthType)
	{
	case Custom: NakamaBP::Client->authenticateCustom(
		std::string(TCHAR_TO_UTF8(*TokenOrID)),
		std::string(TCHAR_TO_UTF8(*Username)),
		Create,
		{},
		Success,
		Error);
		break;
	case Device: NakamaBP::Client->authenticateDevice(
		std::string(TCHAR_TO_UTF8(*TokenOrID)),
		std::string(TCHAR_TO_UTF8(*Username)),
		Create,
		{},
		Success,
		Error);
		break;
	case Facebook: NakamaBP::Client->authenticateFacebook(
        std::string(TCHAR_TO_UTF8(*TokenOrID)),
        std::string(TCHAR_TO_UTF8(*Username)),
        Create,
        ImportFriends,
        {},
        Success,
        Error);
		break;
	case Google: NakamaBP::Client->authenticateGoogle(
        std::string(TCHAR_TO_UTF8(*TokenOrID)),
        std::string(TCHAR_TO_UTF8(*Username)),
        Create,
        {},
        Success,
        Error);
		break;
	case Steam: NakamaBP::Client->authenticateSteam(
        std::string(TCHAR_TO_UTF8(*TokenOrID)),
        std::string(TCHAR_TO_UTF8(*Username)),
        Create,
        {},
        Success,
        Error);
		break;
	default:
		checkNoEntry();
		break;
	}
};

UNakamaAuthenticate * UNakamaAuthenticate::AuthenticateDevice(const FString DeviceID, const FString Username, const bool Create, const FOnAuthSuccessResponse& SuccessDelegate, const FOnErrorResponse& ErrorDelegate)
{
	UNakamaAuthenticate* proxy = NewObject<UNakamaAuthenticate>();
	proxy->AuthType = Device;
	proxy->TokenOrID = DeviceID;
	proxy->Username = Username;
	proxy->Create = Create;
	proxy->OptionalSuccessFunc = SuccessDelegate;
	proxy->OptionalErrorFunc = ErrorDelegate;
	return proxy;
};

UNakamaAuthenticate * UNakamaAuthenticate::AuthenticateCustom(const FString CustomID, const FString Username, const bool Create, const FOnAuthSuccessResponse & SuccessDelegate, const FOnErrorResponse & ErrorDelegate)
{
	UNakamaAuthenticate* proxy = NewObject<UNakamaAuthenticate>();
	proxy->AuthType = Custom;
	proxy->TokenOrID = CustomID;
	proxy->Username = Username;
	proxy->Create = Create;
	proxy->OptionalSuccessFunc = SuccessDelegate;
	proxy->OptionalErrorFunc = ErrorDelegate;
	return proxy;
}

UNakamaAuthenticate* UNakamaAuthenticate::AuthenticateEmail(const FString EmailAddress, const FString Password, const FString Username, const bool Create, const FOnAuthSuccessResponse& SuccessDelegate, const FOnErrorResponse& ErrorDelegate)
{
	UNakamaAuthenticate* proxy = NewObject<UNakamaAuthenticate>();
	proxy->AuthType = Email;
	proxy->TokenOrID = EmailAddress;
	proxy->Password = Password;
	proxy->Username = Username;
	proxy->Create = Create;
	proxy->OptionalSuccessFunc = SuccessDelegate;
	proxy->OptionalErrorFunc = ErrorDelegate;
	return proxy;
};

UNakamaAuthenticate * UNakamaAuthenticate::AuthenticateFacebook(const FString AccessToken, const FString Username, const bool Create, const bool ImportFriends, const FOnAuthSuccessResponse& SuccessDelegate, const FOnErrorResponse& ErrorDelegate)
{
	UNakamaAuthenticate* proxy = NewObject<UNakamaAuthenticate>();
	proxy->AuthType = Facebook;
	proxy->TokenOrID = AccessToken;
	proxy->Username = Username;
	proxy->Create = Create;
	proxy->ImportFriends = ImportFriends;
	proxy->OptionalSuccessFunc = SuccessDelegate;
	proxy->OptionalErrorFunc = ErrorDelegate;
	return proxy;
};

UNakamaAuthenticate * UNakamaAuthenticate::AuthenticateGoogle(const FString AccessToken, const FString Username, const bool Create, const FOnAuthSuccessResponse& SuccessDelegate, const FOnErrorResponse& ErrorDelegate)
{
	UNakamaAuthenticate* proxy = NewObject<UNakamaAuthenticate>();
	proxy->AuthType = Google;
	proxy->TokenOrID = AccessToken;
	proxy->Username = Username;
	proxy->Create = Create;
	proxy->OptionalSuccessFunc = SuccessDelegate;
	proxy->OptionalErrorFunc = ErrorDelegate;
	return proxy;
};

UNakamaAuthenticate * UNakamaAuthenticate::AuthenticateSteam(const FString AccessToken, const FString Username, const bool Create, const FOnAuthSuccessResponse& SuccessDelegate, const FOnErrorResponse& ErrorDelegate)
{
	UNakamaAuthenticate* proxy = NewObject<UNakamaAuthenticate>();
	proxy->AuthType = Steam;
	proxy->TokenOrID = AccessToken;
	proxy->Username = Username;
	proxy->Create = Create;
	proxy->OptionalSuccessFunc = SuccessDelegate;
	proxy->OptionalErrorFunc = ErrorDelegate;
	return proxy;
};
