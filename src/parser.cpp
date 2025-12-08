#include "parser.hpp"

#include <stdint.h>
#include <memory.h>

enum class MessageType {
    SYSTEM_EVENT                = 'S',
    STOCK_DIRECTORY             = 'R',
    STOCK_TRADING_ACTION        = 'H',
    REG_SHO                     = 'Y',
    MARKET_PARTICIPANT_POSITION = 'L',
    MWCB_DECLINE_LEVEL_MESSAGE  = 'V',
    MWCB_STATUS_MESSAGE         = 'W',
    IPO_QUOTING_PERIOD_UPD  = 'K',
    LULD_AUCTION_COLLAR         = 'J',
    OPERATIONAL_HALT            = 'h',

    ADD_ORDER_NO_MPID = 'A',
    ADD_ORDER_MPID    = 'F',

    ORDER_EXECUTED       = 'E',
    ORDER_EXECUTED_PRICE = 'C',
    ORDER_CANCEL         = 'X',
    ORDER_DELETE         = 'D',
    ORDER_REPLACE        = 'U',

    NON_CROSS_TRADE_MSG        = 'P',
    CROSS_TRADE_MSG  = 'Q',
    BROKEN_TRADE_MSG = 'B',

    NOII_MSG = 'I',

    DIRECT_LISTING_CAPITAL_RAISE = 'O',
};


struct SystemEvent {
    uint16_t stock_locate;
    uint16_t tracking_number;
    uint64_t timestamp;
    char     event_code;
};

struct StockDirectory {
    uint16_t stock_locate;
    uint16_t tracking_number;
    uint64_t timestamp;
    char  stock[8];
    char  market_category;
    char  financial_status_indicator;
    uint32_t round_lot_size;
    char round_lots_only;
    char issue_classification;
    char issue_sub_type[2];
    char authenticity;
    char short_sale_threshold_indicator;
    char ipo_flag;
    char luld_reference_price_tier;
    char etp_flag;
    uint32_t etp_leverage_factor;
};

struct TradingAction {
    uint16_t stock_locate;
    uint16_t tracking_number;
    uint64_t timestamp;
    char     stock[8];
    char     trading_state;
    char     reserved;
    char     reason[4];
};

struct RegSho {
    uint16_t locate_code;
    uint16_t tracking_number;
    uint64_t timestamp;
    char     stock[8];
    char     reg_sho_action;
};

struct MarketParticipantPosition {
    uint16_t stock_locate;
    uint16_t tracking_number;
    uint64_t timestamp;
    char     mpid[4];
    char     stock[8];
    char     primary_market_maker;
    char     market_maker_mode;
    char     market_participant_state;
};

struct MwcbDeclineLevel {
    uint16_t stock_locate;
    uint16_t tracking_number;
    uint64_t timestamp;
    uint64_t level1;
    uint64_t level2;
    uint64_t level3;
};

struct MwcbStatus {
    uint16_t stock_locate;
    uint16_t tracking_number;
    uint64_t timestamp;
    char     breached_level;
};

struct IPOQuotingPeriodUpd {
    uint16_t stock_locate;
    uint16_t tracking_number;
    uint64_t timestamp;
    char     stock[8];
    uint32_t ipo_quotation_release_time;
    char     ipo_quatation_release_qualifier;
    uint32_t ipo_price;
};

struct LuldAuctionCollar {
    uint16_t stock_locate;
    uint16_t tracking_number;
    uint64_t timestamp;
    char     stock[8];
    uint32_t auction_collar_reference_price;
    uint32_t upper_auction_collar_price;
    uint32_t lower_auction_collar_price;
    uint32_t auction_collar_extension;
};

struct OperationalHalt {
    uint16_t stock_locate;
    uint16_t tracking_number;
    uint64_t timestamp;
    char     stock[8];
    char     market_code;
    char     operational_halt_action;
};

struct AddOrderNoMpid {
    uint16_t stock_locate;
    uint16_t tracking_number;
    uint64_t timestamp;
    uint64_t order_reference_number;
    char     buy_sell;
    uint32_t shares;
    char     stock[8];
    uint32_t price;
};

struct AddOrderMpid {
    uint16_t stock_locate;
    uint16_t tracking_number;
    uint64_t timestamp;
    uint64_t order_reference_number;
    char     buy_sell;
    uint32_t shares;
    char     stock[8];
    uint32_t price;
    char     attribution[4];
};

struct OrderExecuted {
    uint16_t stock_locate;
    uint16_t tracking_number;
    uint64_t timestamp;
    uint64_t order_reference_number;
    uint32_t executed_shares;
    uint64_t match_number;
};

struct OrderExecutedPrice {
    uint16_t stock_locate;
    uint16_t tracking_number;
    uint64_t timestamp;
    uint64_t order_reference_number;
    uint32_t executed_shares;
    uint64_t match_number;
    char     printable;
    uint32_t execution_price;
};

struct OrderCancel {
    uint16_t stock_locate;
    uint16_t tracking_number;
    uint64_t timestamp;
    uint64_t order_reference_number;
    uint32_t cancelled_shares;
};

struct OrderDelete {
    uint16_t stock_locate;
    uint16_t tracking_number;
    uint64_t timestamp;
    uint64_t order_reference_number;
};

struct OrderReplace {
    uint16_t stock_locate;
    uint16_t tracking_number;
    uint64_t timestamp;
    uint64_t order_reference_number;
    uint64_t new_reference_number;
    uint32_t shares;
    uint32_t price;
};

struct TradeMessageNonCross {
    uint16_t stock_locate;
    uint16_t tracking_number;
    uint64_t timestamp;
    uint64_t order_reference_number;
    char     buy_sell;
    uint32_t shares;
    char     stock[8];
    uint32_t price;
    uint64_t match_number;
};

struct TradeMessageCross {
    uint16_t stock_locate;
    uint16_t tracking_number;
    uint64_t timestamp;
    uint32_t shares;
    char     stock[8];
    uint32_t cross_price;
    uint64_t match_number;
    char     cross_type;
};

struct BrokenTrade {
    uint16_t stock_locate;
    uint16_t tracking_number;
    uint64_t timestamp;
    uint64_t match_number;
};

struct Noii {
    uint16_t stock_locate;
    uint16_t tracking_number;
    uint64_t timestamp;

    uint64_t paired_shares;
    uint64_t imbalance_shares;
    char     imbalance_direction;

    char     stock[8];
    uint32_t far_price;
    uint32_t near_price;
    uint32_t current_reference_price;
    char     cross_type;
    char     price_variation_indicator;
};

struct DirectListingCapitalRaise {
    uint16_t stock_locate;
    uint16_t tracking_number;
    uint64_t timestamp;

    char     stock[8];
    char     open_eligibility_status;
    uint32_t minimum_allowable_price;
    uint32_t maximum_allowable_price;
    uint32_t near_execution_price;
    uint64_t near_execution_time;
    uint32_t lower_price_range_collar;
    uint32_t upper_price_range_collar;
};

struct Message {
    MessageType type;
    union {
        SystemEvent system_event;
        StockDirectory stock_directory;
        TradingAction trading_action;
        RegSho reg_sho;
        MarketParticipantPosition market_participant_pos;
    };
};

inline uint64_t load_be48(const std::byte* p) {
    return (uint64_t(p[0]) << 40) |
           (uint64_t(p[1]) << 32) |
           (uint64_t(p[2]) << 24) |
           (uint64_t(p[3]) << 16) |
           (uint64_t(p[4]) << 8)  |
           uint64_t(p[5]);
}

inline uint64_t load_be64(const std::byte* p) {
    return (uint64_t(p[0]) << 56) |
           (uint64_t(p[1]) << 48) |
           (uint64_t(p[2]) << 40) |
           (uint64_t(p[3]) << 32) |
           (uint64_t(p[4]) << 24) |
           (uint64_t(p[5]) << 16) |
           (uint64_t(p[6]) << 8)  |
           uint64_t(p[7]);
}

inline uint32_t load_be32(const std::byte* p) {
    return (uint32_t(p[0]) << 24) |
           (uint32_t(p[1]) << 16) |
           (uint32_t(p[2]) << 8)  |
           uint32_t(p[3]);
}

inline uint16_t load_be16(const std::byte* p) {
    return (uint16_t(p[0]) << 8) | uint16_t(p[1]);
}

static inline SystemEvent parse_system_event(std::byte const * src) {
    SystemEvent sysEvent;
    sysEvent.stock_locate = load_be16(src);
    src += 2;
    sysEvent.tracking_number = load_be16(src);
    src += 2;
    sysEvent.timestamp = load_be48(src);
    src += 6;
    sysEvent.event_code = char(src[0]);
    src += 1;
    return sysEvent;
}

static inline StockDirectory parse_stock_directory(std::byte const * src) {
    StockDirectory stockDir;
    stockDir.stock_locate = load_be16(src);
    src += 2;

    stockDir.tracking_number = load_be16(src);
    src += 2;

    stockDir.timestamp = load_be48(src);
    src += 6;

    memcpy(&stockDir.stock, src, 8);
    src += 8;

    stockDir.market_category = char(src[0]);
    src += 1;

    stockDir.financial_status_indicator = char(src[0]);
    src += 1;

    stockDir.round_lot_size = load_be32(src);
    src += 4;


}

template <typename Handler>
void ItchParser::parse(std::byte const *  src, size_t len, Handler& handler) {
    std::byte const * end = src + len;
    while (src < end) {
        uint16_t size = __builtin_bswap16(*reinterpret_cast<uint16_t const *>(src));
        src += 2;

        auto type = *reinterpret_cast<MessageType const *>(src);
        switch (type) {
            case MessageType::SYSTEM_EVENT: {
                Message msg{};
                msg.type = type;
                msg.system_event = parse_system_event(src);
                handler.handle(msg);

                break;
            }

            case MessageType::STOCK_DIRECTORY:
                break;

            case MessageType::STOCK_TRADING_ACTION:
                break;

            case MessageType::REG_SHO:
                break;

            case MessageType::MARKET_PARTICIPANT_POSITION:
                break;

            case MessageType::MWCB_DECLINE_LEVEL_MESSAGE:
                break;

            case MessageType::MWCB_STATUS_MESSAGE:
                break;

            case MessageType::IPO_QUOTING_PERIOD_UPD:
                break;

            case MessageType::LULD_AUCTION_COLLAR:
                break;

            case MessageType::OPERATIONAL_HALT:
                break;

            case MessageType::ADD_ORDER_NO_MPID:
                break;

            case MessageType::ADD_ORDER_MPID:
                break;

            case MessageType::ORDER_EXECUTED:
                break;

            case MessageType::ORDER_EXECUTED_PRICE:
                break;

            case MessageType::ORDER_CANCEL:
                break;

            case MessageType::ORDER_DELETE:
                break;

            case MessageType::ORDER_REPLACE:
                break;

            case MessageType::NON_CROSS_TRADE_MSG:
                break;

            case MessageType::CROSS_TRADE_MSG:
                break;

            case MessageType::BROKEN_TRADE_MSG:
                break;

            case MessageType::NOII_MSG:
                break;

            case MessageType::DIRECT_LISTING_CAPITAL_RAISE:
                break;

            default:
                break;
        }


        src += size;
    }
}
