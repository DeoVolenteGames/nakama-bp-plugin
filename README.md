# Nakama Blueprint Plugin for Unreal Engine

This is a plugin for Unreal Engine that exposes some functionality for Nakama to
BP. [Nakama by Heroic Labs][nakama] is a distributed server for social and
realtime games and apps. This plugin relies on the [Nakama C++ plugin for
Unreal][nakama-unreal] for functionality. It's fairly limited at the moment as
I'm adding things based on how important they are to me. Also, there are no
guarantees on the quality of this code. Use at your own risk!

For more information about using Nakama, check out this three part tutorial by
[Knights of Unity][kou-nakama-tutorial], it's for Unity but it should illustrate
usage of Nakama pretty well.

Currently designed and tested with Nakama server version 3.1.1, and Nakama
Unreal version 2.4.0.

## To use

1. Make sure your Unreal project is a C++ project. If it is Blueprint only, you
   can add a new C++ file to your project in Unreal Editor via "File -> New C++
   Class". It doesn't matter what you add; this is only to allow you to compile
   the plugins.
1. If one does not already exist, create a Plugins folder at the root of your
   project.
1. Copy the Nakama C++ plugin into your plugins directory. Follow the
   instructions it has to install, but don't worry about setting it up in code.
1. Copy this plugin into your plugins directory.
1. Build the project solution.

## Info

For JSON parsing in BP I use [Maksim Shestakov JSON plugin][json].

For testing server APIs I use a local [Docker server][nakama-docker] with [Insomnia].

Also, you need to be able to build C++ projects with Unreal, currently I am not distributing binary files.

## Development Progress

### DONE

1. Expand the static module, extends `FTickableGameObject` so we can [do stuff
   on tick][tick].
1. Store data in module, like [`NClientParameters` and `NClientPtr`][connect].
1. Create a way to [send async requests][requests] using
   `UOnlineBlueprintCallProxyBase`.
1. [Authenticate] using client and store the auth token.
1. Create a system to make it a little easier to author nodes to call Nakama
   functions from BP and await a response.
1. Get Account.
1. [RPCs].
1. Storage [reads and writes][read-write].
    1. Read.
    1. Write.
    1. List.
    1. Delete.

### TODO

1. Global error delegate to catch all errors.
1. Friends.
1. Realtime chat.
1. Matchmaking.
1. Realtime multiplayer?
1. Authoritative multiplayer?

[nakama]: https://github.com/heroiclabs/nakama
[nakama-unreal]: https://github.com/heroiclabs/nakama-unreal
[kou-nakama-tutorial]: https://blog.theknightsofunity.com/nakama-tutorial-1/
[json]: https://www.unrealengine.com/marketplace/en-US/product/json-blueprint
[nakama-docker]: https://heroiclabs.com/docs/install-docker-quickstart/
[insomnia]: https://insomnia.rest/
[tick]: https://heroiclabs.com/docs/unreal-client-guide/#tick
[connect]: https://heroiclabs.com/docs/unreal-client-guide/#usage
[requests]: https://heroiclabs.com/docs/unreal-client-guide/#send-requests
[authenticate]: https://heroiclabs.com/docs/unreal-client-guide/#authenticate
[rpcs]: https://heroiclabs.com/docs/runtime-code-basics/
[read-write]: https://heroiclabs.com/docs/storage-collections/
