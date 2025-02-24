#include "Core.h"
#include <fstream>

#include <iostream>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>

namespace Core {

	void DbConnectionString() {
		try {
			mongocxx::instance inst{};
			const auto uri = mongocxx::uri{ "mongodb+srv://itspecialistt:qWer50ty@cluster0.ub06h.mongodb.net/?retryWrites=true&w=majority&appName=Cluster0" };

			// MongoDB bağlantı ayarları
			mongocxx::options::client client_options;
			const auto api = mongocxx::options::server_api{ mongocxx::options::server_api::version::k_version_1 };
			client_options.server_api_opts(api);

			// Bağlantıyı oluştur
			mongocxx::client conn{ uri, client_options };
			mongocxx::database db = conn["admin"];

			// Ping atarak bağlantıyı test et
			const auto ping_cmd = bsoncxx::builder::basic::make_document(bsoncxx::builder::basic::kvp("ping", 1));
			db.run_command(ping_cmd.view());

			std::cout << "Pinged your deployment. You successfully connected to MongoDB!" << std::endl;
		}
		catch (const std::exception& e) {
			std::cerr << "MongoDB bağlantı hatası: " << e.what() << std::endl;
		}
	}

	void dbSentData(const std::string& file_path) {
		try {
			mongocxx::instance inst{};
			mongocxx::client client{ mongocxx::uri{"mongodb+srv://itspecialistt:qWer50ty@cluster0.ub06h.mongodb.net/?retryWrites=true&w=majority&appName=Cluster0"} };

			auto db = client["mydatabase"];
			auto bucket = db.gridfs_bucket();

			std::ifstream file(file_path, std::ios::binary);
			if (!file) {
				std::cerr << "Dosya açılamadı: " << file_path << std::endl;
				return;
			}

			std::vector<char> file_data((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
			auto uploader = bucket.open_upload_stream(file_path);
			uploader.write(file_data.data(), file_data.size());
			uploader.close();

			std::cout << "Dosya başarıyla yüklendi: " << file_path << std::endl;

		}
		catch (const std::exception& e) {
			std::cerr << "Dosya yükleme hatası: " << e.what() << std::endl;
		}
	}
	void dbInsert() {
		try {
			mongocxx::instance inst{};
			mongocxx::client client{ mongocxx::uri{"mongodb+srv://itspecialistt:qWer50ty@cluster0.ub06h.mongodb.net/?retryWrites=true&w=majority&appName=Cluster0"} };
			auto db = client["mydatabase"];
			auto collection = db["mycollection"];

			bsoncxx::builder::basic::document doc{};
			doc.append(bsoncxx::builder::basic::kvp("name", "Ozan"));
			doc.append(bsoncxx::builder::basic::kvp("age", 25));

			collection.insert_one(doc.view());

			std::cout << "Belge başarıyla MongoDB'ye eklendi!" << std::endl;

		}
		catch (const std::exception& e) {
			std::cerr << "Veri ekleme hatası: " << e.what() << std::endl;
		}
	}
}
