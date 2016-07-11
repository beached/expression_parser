// The MIT License (MIT)
//
// Copyright (c) 2014-2015 Darrell Wright
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files( the "Software" ), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once
#include <boost/utility/string_ref.hpp>
#include <memory>

namespace daw {
	namespace expression_parser {
		namespace ast {
			struct expression {
				virtual ~expression( );
			};	// expression

			struct value: public expression {
				virtual ~value( );
			};	// value

			struct variable: public value, public expression {
				virtual ~variable( );
				std::string name;
			};	// variable

			struct constant: public value, public expression {
				virtual ~constant( );
			};	// constant
			
			struct function: public expression {
				virtual ~function( );
				std::string name;
				std::vector<std::shard_ptr<expression>> parameters;
			};	// function

			struct operators: public expression {
				virtual ~operators( );
				std::shared_ptr<expression> left_operand;
				std::shared_ptr<expression> right_operand;
			};		// operators

			struct operator_add: public operators {
				virtual ~operator_add( );
			};	// operator_add

			struct operator_del: public operators {
				virtual ~operator_del( );
			};	// operator_del

			struct operator_mul: public operators {
				virtual ~operator_mul( );
			};	// operator_mul

			struct operator_div: public operators {
				virtual ~operator_div( );
			};	// operator_div

			struct sum: public expression {
				virtual ~sum( );
				std::shared_ptr<value> starting_point;
				std::shared_ptr<value> stoping_point;
				std::shared_ptr<variable> index;
				std::shared_ptr<expression> element;
			};	// sum

			struct control_statement: public expression {
				virtual ~control_statement( );
			};	// control_statement


			struct constrol_statement_if: public control_statement {
				virtual ~control_statement_if( );
				std::vector<std::pair<expression, expression>> cases;
			}
		}	// namespace ast

		std::shared_ptr<ast::expression> evaluation( boost::string_ref expression_string );

		std::shared_ptr<ast::expression> simplify( std::shared_ptr<ast::expression> e );

	}	// namespace expression_parser
}	// namespace daw

