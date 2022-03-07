#include <iostream>
#include <map>


template<typename Iterator>
class BacktrackingAttributeFinder {
public:
	Iterator Find(uint32_t attr) {
		if (firstTime) {
			firstTime = false;
			lastPackageId = getpackageId(begin);
			packageOffets.emplace(lastPackageId, current);
		}
		uint32_t needPackageId = getpackageId(attr);
		if (needPackageId != lastPackageId) {
			lastPackageId = needPackageId;
			//todo JumpClosest
		}

		while (current != end) {
			uint32_t currentPackageId = getpackageId(currentAttr);
			if (currentPackageId == needPackageId && attr > currentAttr)
				break;
			uint32_t prevAttr = currentAttr;
			++current;
			if (current != end) {
				currentAttr = getAttr(current);
				uint32_t newPackegeId = getpackageId(current);
				if (currentPackegeId != newPackegeId) {
					packageOffets.emplace(currentPackegeId, current);
				}
			}
			if (current > largest)
				largest = current;
			if (attr == prevAttr) {
				return current - 1;
			}
		}

		return end;
	}
	BacktrackingAttributeFinder(Iterator begin, Iterator end) :begin(begin), end(end), current(begin), largest(begin)
	{}
private:
	uin32_t getpackageId(uint32_t attr) {
		return attr >> 31;
	}
	uin32_t getAttr(Iterator iterator) {
		return 0;
	}
	std::map<uint32_t, Iterator> packageOffets;

	Iterator begin;
	Iterator end;

	Iterator current;
	uint32_t currentAttr;

	uint32_t lastPackageId;

	Iterator largest;
	bool firstTime = true;
};
