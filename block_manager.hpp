#pragma once
#include <map>
#include "std_micro_service.hpp"

typedef std::array<uint8_t, 32> Hash;
typedef std::array<uint8_t, 64> Signature;
typedef std::array<uint8_t, 32> PubKey;

struct Input {
	Hash hash;
	uint32_t index;
	Signature sig;
};

struct Output {
	uint32_t amount;
	PubKey   key;
};

typedef struct Transaction {
	std::vector<Input> inputs;
	std::vector<Output> outputs;
}TransactionInfo;

typedef struct {
	std::string previous;
	std::string height;
	std::string nonce;
	std::vector<Transaction> transaction;
} BlockInformation;
class BlockManagerException : public std::exception {
	std::string _message;
public:
	BlockManagerException(const std::string & message) :
		_message(message) { }
	const char * what() const throw() {
		return _message.c_str();
	}
};
// alias declaration of our In Memory database...
using BlockDatabase = std::map<std::string, BlockInformation>;
class BlockManager {
public:
	std::string transaction(const TransactionInfo & transInfo)
		throw(BlockManagerException);
	std::string block(BlockInformation & blockInfo);
};