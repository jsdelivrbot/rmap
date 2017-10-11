/**@file ethernet_config.h */

/*********************************************************************
Copyright (C) 2017  Marco Baldinetti <m.baldinetti@digiteco.it>
authors:
Paolo patruno <p.patruno@iperbole.bologna.it>
Marco Baldinetti <m.baldinetti@digiteco.it>

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of
the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
**********************************************************************/

#ifndef _ETHERNET_CONFIG_H
#define _ETHERNET_CONFIG_H

#define ETHERNET_DEFAULT_DHCP_ENABLE      (true)
#define ETHERNET_DEFAULT_MAC              ("E2:21:B6:44:EB:29")
#define ETHERNET_DEFAULT_IP               ("192.168.0.99")
#define ETHERNET_DEFAULT_NETMASK          ("255.255.255.0")
#define ETHERNET_DEFAULT_GATEWAY          ("192.168.0.2")
#define ETHERNET_DEFAULT_PRIMARY_DNS      ("192.168.0.1")

#define ETHERNET_DEFAULT_LOCAL_UDP_PORT   (8000)

#define ETHERNET_ATTEMPT_MS               (2000)

#define ETHERNET_RETRY_TIME_MS            (2000)
#define ETHERNET_RETRY_COUNT              (2)

#define ETHERNET_TIMEOUT_MS               (2000)

#define ETHERNET_MAC_LENGTH               (6)
#define ETHERNET_IP_LENGTH                (4)

#endif
