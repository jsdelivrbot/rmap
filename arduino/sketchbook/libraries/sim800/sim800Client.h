/**@file sim800Client.h */

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

#ifndef Client_h
#define Client_h

#include "sim800.h"

class sim800Client : public SIM800 {

 public:
  sim800Client();
  int connect(IPAddress ip, int port);
  int connect(const char *host, int port);
  uint8_t connected();
  int available();
  int read();
  int readBytes(char *buffer, size_t size);
  int readBytes(uint8_t *buffer, size_t size);
  void setTimeout(uint32_t timeout);
  size_t write(uint8_t);
  size_t write(const uint8_t *buffer, size_t size);
  void flush();
  void stop();
  bool transparentescape();
  bool transparent();
};

#endif
