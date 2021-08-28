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

Currently designed and tested with Nakama server version 3.1.1, Nakama
Unreal version 2.4.0, and Unreal Engine 4.26.2.

## Getting Started

1. Make sure your Unreal project is a C++ project. If it is Blueprint only, you
   can add a new C++ file to your project in Unreal Editor via "File -> New C++
   Class". It doesn't matter what you add; this is only to allow you to compile
   the plugins.
1. If one does not already exist, create a Plugins folder at the root of your
   project.
1. Copy the [Nakama C++ plugin for Unreal][nakama-unreal] into your project's
   plugins directory. Follow the instructions it has to install, but don't worry
   about setting it up in code.
1. Copy this plugin into a folder in your project's plugins directory.
1. Build the project solution and open the project.
1. Create a client using the `Create Nakama Client` node. A good place to put
   this is in your game instance. If you're only testing you don't need to
   change any of the arguments (in fact this node isn't required when testing)
   but in production you'll want to set the host address at least.
1. Authenticate using one of the authentication nodes. For testing it can be
   good to start with custom authentication.
1. On the success of your authentication then you're good to go! Try testing it
   out with the `Get Account` node.

## Info

For JSON parsing in BP I use [Maksim Shestakov's JSON plugin][json].

For testing server APIs I use a local [Docker server][nakama-docker] with
[Insomnia].

Also, to use this plugin you still need to be able to build C++ projects with
Unreal as I'm not distributing binary files currently.

Currently cannot test real time MP in editor because the client session is
stored as a static variable. For testing you need to have a separate process, so
right click the project file and select `Launch Game` to open another client to
test with. Currently considering changing the design to make it easier to test
RT MP in the editor.

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
1. Matchmaking.
   1. Add user to matchmaking.
   1. Remove user from matchmaking.
   1. Automatically join RT match?
1. [Realtime (RT) multiplayer][rtclient]. Uses NakamaClientSubsystem to track state.
   **NEEDS TESTING**.
   1. [Add callback to receive messages][rtclient-callback].
   1. Send messages.
   1. Create match.
   1. Join match by ID.
   1. Leave match.

### TODO

1. Fix cursor in ListUserStorageObjects. Requires [next version of Nakama
   plugin][list-cursor-issue].
1. Matchmaking.
   1. Help generate Bleve queries?
   1. Automatically join match via IP with UE4 networking?
   1. Allow for manually joining matches.
1. [Realtime multiplayer][rtclient]?
   1. List opponents.
1. Friends.
    1. Add.
    1. List.
    1. Remove.
    1. Block.
1. Global error delegate to catch all errors.
1. Realtime chat.
   1. Join chat room.
   1. Send messages.
   1. Receive messages.
   1. Leave chat room.
   1. Other commands...
1. Authoritative multiplayer? *There might not be any point providing helpers
   for this once everything else is done*.

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
[list-cursor-issue]: https://github.com/heroiclabs/nakama-unreal/issues/47#issuecomment-839185667
[rtclient]: https://heroiclabs.github.io/nakama-cpp/html/class_n_rt_default_client_listener.html
[rtclient-callback]: https://heroiclabs.github.io/nakama-cpp/html/class_n_rt_default_client_listener.html#aef5c02769cd03398dea002e64bfc980f
