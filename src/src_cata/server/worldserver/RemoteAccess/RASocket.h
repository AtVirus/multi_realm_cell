/*
 * Copyright (C) Likan Mod   (https://github.com/ChaosDevLikan/)
 * Copyright (C) Prydev      (http://sourceforge.net/projects/prydevserver) 
 * Copyright (C) TrinityCore (http://www.trinitycore.org)
 * Copyright (C) MaNGOS      (http://www.getmangos.com)
 * Copyright (C) ArkCORE     (http://www.arkania.net)
 * Copyright (C) SkyFireEMU  (http://www.projectskyfire.org)
 *
 * World of Warcraft
 * You can edit but you can not delete this copyright.
 * Genesis Emulator - Genesis Database 
 *
 *
 * By Likan Developer Core C++, SQL (FUN, WoTLK, Cata Realm) of Genesis Server
 */

/// \addtogroup Trinityd
/// @{
/// \file

#ifndef _RASOCKET_H
#define _RASOCKET_H

#include "Common.h"

#include <ace/Synch_Traits.h>
#include <ace/Svc_Handler.h>
#include <ace/SOCK_Stream.h>
#include <ace/SOCK_Acceptor.h>

/// Remote Administration socket
class RASocket: public ACE_Svc_Handler<ACE_SOCK_STREAM, ACE_MT_SYNCH>
{
    public:
        RASocket();
        virtual ~RASocket();

        virtual int svc(void);
        virtual int open(void * = 0);
        virtual int handle_close(ACE_HANDLE = ACE_INVALID_HANDLE, ACE_Reactor_Mask = ACE_Event_Handler::ALL_EVENTS_MASK);

    private:
        int recv_line(std::string& out_line);
        int recv_line(ACE_Message_Block& buffer);
        int process_command(const std::string& command);
        int authenticate();
        int subnegotiate();     //! Used by telnet protocol RFC 854 / 855
        int check_access_level(const std::string& user);
        int check_password(const std::string& user, const std::string& pass);
        int send(const std::string& line);

        static void zprint(void* callbackArg, const char * szText );
        static void commandFinished(void* callbackArg, bool success);

    private:
        /// Minimum security level required to connect
        uint8 _minLevel;
        ACE_Atomic_Op<ACE_Thread_Mutex, bool> _commandExecuting;
};
#endif
/// @}
