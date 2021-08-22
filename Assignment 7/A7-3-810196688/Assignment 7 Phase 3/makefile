CC=g++
STD=-std=c++11 -Wall -pedantic
CF=$(STD)
BUILD_DIR=build
TEMPLATE_DIR=.template

all: $(BUILD_DIR) myserver.out

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/Shop.o: Phase3/Shop.cpp Phase3/Shop.hpp Phase3/Product.hpp Phase3/User.hpp Phase3/Admin.hpp Phase3/Program_errors.hpp
	$(CC) $(CF) -c Phase3/Shop.cpp -o $(BUILD_DIR)/Shop.o

$(BUILD_DIR)/User.o: Phase3/User.cpp Phase3/User.hpp Phase3/Offer.hpp
	$(CC) $(CF) -c Phase3/User.cpp -o $(BUILD_DIR)/User.o

$(BUILD_DIR)/Product.o: Phase3/Product.cpp Phase3/Product.hpp Phase3/Comment.hpp
	$(CC) $(CF) -c Phase3/Product.cpp -o $(BUILD_DIR)/Product.o

$(BUILD_DIR)/Offer.o: Phase3/Offer.cpp Phase3/Offer.hpp Phase3/Discount.hpp
	$(CC) $(CF) -c Phase3/Offer.cpp -o $(BUILD_DIR)/Offer.o

$(BUILD_DIR)/Discount.o: Phase3/Discount.cpp Phase3/Discount.hpp
	$(CC) $(CF) -c Phase3/Discount.cpp -o $(BUILD_DIR)/Discount.o

$(BUILD_DIR)/Comment.o: Phase3/Comment.cpp Phase3/Comment.hpp
	$(CC) $(CF) -c Phase3/Comment.cpp -o $(BUILD_DIR)/Comment.o

$(BUILD_DIR)/Admin.o: Phase3/Admin.cpp Phase3/Admin.hpp Phase3/User.hpp
	$(CC) $(CF) -c Phase3/Admin.cpp -o $(BUILD_DIR)/Admin.o

$(BUILD_DIR)/Buyer.o: Phase3/Buyer.cpp Phase3/Buyer.hpp Phase3/User.hpp Phase3/Offer.hpp Phase3/Program_errors.hpp
	$(CC) $(CF) -c Phase3/Buyer.cpp -o $(BUILD_DIR)/Buyer.o

$(BUILD_DIR)/Seller.o: Phase3/Seller.cpp Phase3/Seller.hpp Phase3/User.hpp Phase3/Offer.hpp
	$(CC) $(CF) -c Phase3/Seller.cpp -o $(BUILD_DIR)/Seller.o

$(BUILD_DIR)/Car.o: Phase3/Car.cpp Phase3/Car.hpp Phase3/Product.hpp
	$(CC) $(CF) -c Phase3/Car.cpp -o $(BUILD_DIR)/Car.o

$(BUILD_DIR)/TV.o: Phase3/TV.cpp Phase3/TV.hpp Phase3/Product.hpp
	$(CC) $(CF) -c Phase3/TV.cpp -o $(BUILD_DIR)/TV.o

$(BUILD_DIR)/Phone.o: Phase3/Phone.cpp Phase3/Phone.hpp Phase3/Product.hpp
	$(CC) $(CF) -c Phase3/Phone.cpp -o $(BUILD_DIR)/Phone.o

$(BUILD_DIR)/template_parser.o: utils/template_parser.cpp utils/template_parser.hpp utils/request.cpp utils/request.hpp utils/utilities.hpp utils/utilities.cpp
	$(CC) $(CF) -c utils/template_parser.cpp -o $(BUILD_DIR)/template_parser.o

$(BUILD_DIR)/response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	$(CC) $(CF) -c utils/response.cpp -o $(BUILD_DIR)/response.o

$(BUILD_DIR)/request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	$(CC) $(CF) -c utils/request.cpp -o $(BUILD_DIR)/request.o

$(BUILD_DIR)/utilities.o: utils/utilities.cpp utils/utilities.hpp
	$(CC) $(CF) -c utils/utilities.cpp -o $(BUILD_DIR)/utilities.o

$(BUILD_DIR)/server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp utils/template_parser.hpp utils/template_parser.cpp
	$(CC) $(CF) -c server/server.cpp -o $(BUILD_DIR)/server.o

$(BUILD_DIR)/route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c server/route.cpp -o $(BUILD_DIR)/route.o

$(BUILD_DIR)/handlers.o: Phase3/handlers.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c Phase3/handlers.cpp -o $(BUILD_DIR)/handlers.o

$(BUILD_DIR)/ShopServer.o: Phase3/ShopServer.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c Phase3/ShopServer.cpp -o $(BUILD_DIR)/ShopServer.o

$(BUILD_DIR)/main.o: Phase3/main.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c Phase3/main.cpp -o $(BUILD_DIR)/main.o

myserver.out: $(BUILD_DIR)/ShopServer.o $(BUILD_DIR)/main.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/template_parser.o $(BUILD_DIR)/Admin.o $(BUILD_DIR)/Buyer.o $(BUILD_DIR)/Car.o $(BUILD_DIR)/Phone.o $(BUILD_DIR)/Product.o $(BUILD_DIR)/Seller.o $(BUILD_DIR)/Shop.o $(BUILD_DIR)/TV.o $(BUILD_DIR)/Offer.o $(BUILD_DIR)/User.o $(BUILD_DIR)/Comment.o $(BUILD_DIR)/Discount.o
	$(CC) $(CF) $(BUILD_DIR)/ShopServer.o $(BUILD_DIR)/main.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/template_parser.o $(BUILD_DIR)/Admin.o $(BUILD_DIR)/Buyer.o $(BUILD_DIR)/Car.o $(BUILD_DIR)/Phone.o $(BUILD_DIR)/Product.o $(BUILD_DIR)/Seller.o $(BUILD_DIR)/Shop.o $(BUILD_DIR)/TV.o $(BUILD_DIR)/Offer.o $(BUILD_DIR)/User.o $(BUILD_DIR)/Comment.o $(BUILD_DIR)/Discount.o  -o myserver.out

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(TEMPLATE_DIR) *.o *.out &> /dev/null
