#include "asm.h"

void        parser(t_asm *bler)
{
    parse_name_comm(bler); // TODO запарсить имя и комментарий
    parse_commands(bler);
}

