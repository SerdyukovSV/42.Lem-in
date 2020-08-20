#include "../includes/lemin.h"

// void    set_flow(t_lemin *lemin, int flow)
// {
//     int flow_ant;
//     int ants;
//     int i;

//     i = 0;
//     flow_ant = 0;
//     ants = lemin->ants;
//     while (lemin->paths[i])
//     {
//         lemin->paths[i]->flow = 0;
//         flow_ant = flow - lemin->paths[i]->len + 1;
//         if (flow_ant < ants)
//             lemin->paths[i]->flow = flow_ant;
//         else
//             lemin->paths[i]->flow = ants;
//         ants -= lemin->paths[i]->flow;
//         i++;
//     }
// }

// int     get_flow(t_path **paths, int ants)
// {
//     int ln;
//     float flow1;
//     float flow2;
//     int count;

//     ln = 0;
//     count = 0;
//     flow1 = INT32_MAX;
//     flow2 = INT32_MAX;
//     while (paths[count])
//     {
//         ln += paths[count++]->len - 1;
//         flow1 = ((float)ln + ants - 1) / count;
//         if (flow1 < flow2)
//             flow2 = flow1;
//         else
//             break ;
//     }
//     return (flow2);
// }