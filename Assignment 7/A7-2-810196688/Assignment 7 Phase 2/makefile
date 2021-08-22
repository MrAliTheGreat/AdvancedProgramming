CA4_Ali.out : main.o Admin.o Buyer.o Car.o Phone.o Product.o Seller.o Shop.o TV.o Offer.o User.o Comment.o Discount.o
	      g++ -std=c++11 main.o Admin.o Buyer.o Car.o Phone.o Product.o Seller.o Shop.o TV.o Offer.o User.o Comment.o Discount.o

main.o: main.cpp Shop.hpp
	g++ -c main.cpp

Shop.o: Shop.cpp Shop.hpp Product.hpp User.hpp Admin.hpp Program_errors.hpp Model.hpp
	g++ -c Shop.cpp

User.o: User.cpp User.hpp Offer.hpp
	g++ -c User.cpp

Product.o: Product.cpp Product.hpp Comment.hpp
	g++ -c Product.cpp

Offer.o: Offer.cpp Offer.hpp Discount.hpp
	g++ -c Offer.cpp

Discount.o: Discount.cpp Discount.hpp
	g++ -c Discount.cpp

Comment.o: Comment.cpp Comment.hpp
	g++ -c Comment.cpp

Admin.o: Admin.cpp Admin.hpp User.hpp
	g++ -c Admin.cpp

Buyer.o: Buyer.cpp Buyer.hpp User.hpp Offer.hpp Program_errors.hpp
	g++ -c Buyer.cpp

Seller.o: Seller.cpp Seller.hpp User.hpp Offer.hpp
	g++ -c Seller.cpp

Car.o: Car.cpp Car.hpp Product.hpp
	g++ -c Car.cpp

TV.o: TV.cpp TV.hpp Product.hpp
	g++ -c TV.cpp

Phone.o: Phone.cpp Phone.hpp Product.hpp
	g++ -c Phone.cpp

clean:
	rm *.o
