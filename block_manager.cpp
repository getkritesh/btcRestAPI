#include <mutex>
#include "block_manager.hpp"
BlockDatabase blockDB;
std::mutex blockDBMutex;
 std::string BlockManager::transaction(const TransactionInfo & transInfo) throw(BlockManagerException) {

	std::unique_lock<std::mutex> lock{ blockDBMutex };
	//Integrate With PritTransaction 
	std::string transaction = "Transaction";
	return transaction;
}
 std::string BlockManager::block(BlockInformation & blockInfo) {

	//Integrate With PritBlock() 
	 std::string blockInformation = "Block Information";
	return blockInformation;
}