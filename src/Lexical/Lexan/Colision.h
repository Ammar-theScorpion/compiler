#pragma once
#include"Lexical/Core.h"
#include"amcpch.h"
namespace Amc {

	template<typename T>
	struct Node
	{
		T string;
		Node* next = nullptr;
		int grammer=0;
	};
	template<typename T>
	class AMC_API Collision {
		public:
			Collision() {
				nodeHead = nullptr;
				nodeTile = nullptr;
			}
			void pass(...) {}

			template<typename ... S >
			void fetch(S ...args) {
				pass(construct(args)...);
			}
		
			template<typename S >
			int construct(const S& thing) {
				Node<T>* tmp = new Node<T>;
			 
				tmp->string = thing;
				tmp->next = nullptr;

				if (nodeHead == nullptr){
					nodeHead = tmp;
					nodeTile = tmp;
				}
				else{
					nodeTile->next = tmp;
					nodeTile = nodeTile->next;
				} 
				 

				return 0;
			}
			template<>
			int construct(const int& thing) {
				Node<T>* tmp = new Node<T>;
				tmp = nodeHead->next;
				while (tmp != nullptr) {
					if (tmp->grammer == 0) {
						tmp->grammer = thing;
						return 0;
					}
					tmp = tmp->next;

				}
				return 0;
			}
			T value()const {
				return nodeHead->string;
			}
			Node< T>* nodeHead;
			Node< T>* nodeTile;
			int grammer;
	};
}