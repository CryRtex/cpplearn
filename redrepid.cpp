#include <iostream>
#include <hiredis/hiredis.h>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

void redisToJson(redisContext *context) {
    // JSON belgesi oluştur
    rapidjson::Document document;
    document.SetObject();
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

    // Redis'ten verileri al
    redisReply *reply = (redisReply *)redisCommand(context, "KEYS *");
    if (reply == nullptr) {
        std::cerr << "Error: " << context->errstr << std::endl;
        return;
    }

    // Her bir anahtar için değer al ve JSON'a ekle
    for (size_t i = 0; i < reply->elements; ++i) {
        const char* key = reply->element[i]->str;

        // Değeri al
        redisReply *valueReply = (redisReply *)redisCommand(context, "GET %s", key);
        if (valueReply != nullptr && valueReply->type == REDIS_REPLY_STRING) {
            // JSON'a ekle
            document.AddMember(rapidjson::StringRef(key), rapidjson::StringRef(valueReply->str), allocator);
        }
        freeReplyObject(valueReply);
    }
    freeReplyObject(reply);

    // JSON'u yazdır
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);
    std::cout << "JSON Output: " << buffer.GetString() << std::endl;
}

int main() {
    // Redis sunucusuna bağlan
    redisContext *context = redisConnect("127.0.0.1", 6379);
    if (context == nullptr || context->err) {
        if (context) {
            std::cerr << "Redis error: " << context->errstr << std::endl;
            redisFree(context);
        } else {
            std::cerr << "Can't allocate redis context" << std::endl;
        }
        return 1;
    }

    // Redis verilerini JSON'a aktar
    redisToJson(context);

    // Bağlantıyı kapat
    redisFree(context);
    return 0;
}
