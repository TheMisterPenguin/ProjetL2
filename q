SHUTDOWN(8)                                                                                                      shutdown                                                                                                      SHUTDOWN(8)

NNAAMMEE
       shutdown - Halt, power-off or reboot the machine

SSYYNNOOPPSSIISS
       sshhuuttddoowwnn [OPTIONS...] [TIME] [WALL...]

DDEESSCCRRIIPPTTIIOONN
       sshhuuttddoowwnn may be used to halt, power-off or reboot the machine.

       The first argument may be a time string (which is usually "now"). Optionally, this may be followed by a wall message to be sent to all logged-in users before going down.

       The time string may either be in the format "hh:mm" for hour/minutes specifying the time to execute the shutdown at, specified in 24h clock format. Alternatively it may be in the syntax "+m" referring to the specified number of
       minutes m from now.  "now" is an alias for "+0", i.e. for triggering an immediate shutdown. If no time argument is specified, "+1" is implied.

       Note that to specify a wall message you must specify a time argument, too.

       If the time argument is used, 5 minutes before the system goes down the /run/nologin file is created to ensure that further logins shall not be allowed.

OOPPTTIIOONNSS
       The following options are understood:

       ----hheellpp
           Print a short help text and exit.

       --HH, ----hhaalltt
           Halt the machine.

       --PP, ----ppoowweerrooffff
           Power-off the machine (the default).

       --rr, ----rreebboooott
           Reboot the machine.

       --hh
           Equivalent to ----ppoowweerrooffff, unless ----hhaalltt is specified.

       --kk
           Do not halt, power-off, reboot, just write wall message.

       ----nnoo--wwaallll
           Do not send wall message before halt, power-off, reboot.

       --cc
           Cancel a pending shutdown. This may be used to cancel the effect of an invocation of sshhuuttddoowwnn with a time argument that is not "+0" or "now".

EEXXIITT SSTTAATTUUSS
       On success, 0 is returned, a non-zero failure code otherwise.

SSEEEE AALLSSOO
       ssyysstteemmdd(1), ssyysstteemmccttll(1), hhaalltt(8), wwaallll(1)

systemd 249                                                                                                                                                                                                                    SHUTDOWN(8)
