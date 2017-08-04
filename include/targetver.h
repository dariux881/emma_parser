#pragma once

// L'inclusione di SDKDDKVer.h definisce la piattaforma Windows pi� recente disponibile.

// Se si desidera compilare l'applicazione per una piattaforma Windows precedente, includere WinSDKVer.h e
// impostare la macro _WIN32_WINNT sulla piattaforma da supportare prima di includere SDKDDKVer.h.

#if defined WIN32 || _WIN64
#include <SDKDDKVer.h>
#endif
