-- Author:                 Nikita Edward Baruzdin
-- Contact email:          nikita.edward.baruzdin@gmail.com
-- Creation date:          2013-07-21
-- Last modification date: 2013-07-21


require("L4")

local ld = L4.default_loader
local channel = ld:new_channel()

ld:start( { caps = {channel_cap = channel:svr()},
            log  = {"server", "yellow"} },
          "rom/encryption-server" )

ld:start( { caps = {channel_cap = channel},
            log  = {"client", "green"} },
          "rom/encryption-client" )
