/**
 * @file apiDefinition.h
 * @author ayano
 * @date 1/31/24
 * @brief
*/

#ifndef YASASHIISERVER_APIDEFINITION_H
#define YASASHIISERVER_APIDEFINITION_H

namespace YasashiiServer {
    constexpr char RELATE[] = "/queue/relate";
    constexpr char UNRELATE[] = "/queue/unrelate";
    constexpr char TIMEOUT[] = "/queue/set_timeout";
    constexpr char SAFE_TIMEOUT[] = "/queue/set_safe_timeout";
    constexpr char CONSUMER_SUBSCRIBE[] = "/consumer/subscribe";
    constexpr char CONSUMER_UNSUBSCRIBE[] = "/consumer/unsubscribe";
    constexpr char FETCH[] = "/consumer/fetch";
    constexpr char FETCH_ALL[] = "/consumer/fetch_all";
    constexpr char PRODUCER_SUBSCRIBE[] = "/producer/subscribe";
    constexpr char PRODUCER_UNSUBSCRIBE[] = "/producer/unsubscribe";
    constexpr char SEND_BASE[] = "/producer/send/";
    constexpr char BROADCAST_BASE[] = "/producer/broadcast/";
}

#endif //YASASHIISERVER_APIDEFINITION_H
