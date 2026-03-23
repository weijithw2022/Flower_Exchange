#ifndef EXECSTATUS_H
#define EXECSTATUS_H

enum class ExecStatus {
    New      = 0,
    Rejected = 1,
    Fill     = 2,
    PFill    = 3
};

#endif
