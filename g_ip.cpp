
/**
 *
 * 随机生成大量IP地址，输出到标准输出
 *
 */

#include <iostream>
#include <unordered_set>
#include <random>
#include <cstdint>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
    std::random_device r;
    std::default_random_engine el(r());
    std::uniform_int_distribution<uint32_t> dist(0, 0xFFFFFFFF);
    std::unordered_set<uint32_t> ret;
    for (int i = 0; i < 1000000; ++i) {
        auto e = dist(el);
        while (ret.find(e) != ret.end()) {
            e = dist(el);
        }
        ret.insert(e);
    }
    struct in_addr in;
    for(auto e : ret) {
        in.s_addr = e;
        std::cout << inet_ntoa(in) << std::endl;
    }
    return 0;
}
