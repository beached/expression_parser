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

#include "expression_parser.h"
#include <unordered_map>
#include <vector>
#include <utility>

namespace daw {
	namespace expression_parser {
		namespace ast {
				expression::~expression( ) { }
				value::~value( ) { }
				variable::~variable( ) { }
				constant::~constant( ) { }
				function::~function( ) { }
				operators::~operators( ) { }
				operator_add::~operator_add( ) { }
				operator_del::~operator_del( ) { }
				operator_mul::~operator_mul( ) { }
				operator_div::~operator_div( ) { }
				sum::~sum( ) { }
				control_statement::~control_statement( ) { }
				control_statement_if::~control_statement_if( ) { }
		}	// namespace ast

		namespace impl {
			namespace {
				template<typename Iterator>
				struct parser_result_t {
					bool found;
					Iterator first;
					Iterator last;
					
					parser_result_t( bool is_found, Iterator First, Iterator Last ):
						found{ is_found },
						first{ First },
						last{ Last } { }
				};	// parser_result_t

				template<typename Iterator>
				auto parser_result( bool is_found, Iterator first, Iterator last ) {
					return parser_result_t<Iterator>{ is_found, first, last };
				}

				template<typename Iterator>
				auto is_bracket( Iterator pos, Iterator end_pos ) {
					auto result = parser_result( false, pos, end_pos );	
					
					std::vector<Iterator> bracket_stack;

					switch( *pos ) {
						case '(':
						case '[':
						case '{':
							bracket_stack.push_back( pos );
						break;
						default:
							return result;
					}

					while( ++pos != end_pos && !bracket_stack.empty( ) ) {
						switch( *pos ) {
							case '(':
							case '[':
							case '{':
								bracket_stack.push_back( pos );
							break;
							case ')':
								if( *bracket_stack.front( ) != '(' ) {
									throw make_mismatched_bracket_exception( bracket_stack.front( ), pos );
								}
								bracket_stack.pop_back( );
							break;
							case '}':
								if( *bracket_stack.front( ) != '{' ) {
									throw make_mismatched_bracket_exception( bracket_stack.front( ), pos );
								}
								bracket_stack.pop_back( );
							break;
							case ']':
								if( *bracket_stack.front( ) != '[' ) {
									throw make_mismatched_bracket_exception( bracket_stack.front( ), pos );
								}
								bracket_stack.pop_back( );
							break;
							default:
							result.last = pos;
						}
					}
					if( bracket_stack.empty( ) ) {
						result.found = true;
					}
					return result;
				}

				struct functions {
					static auto function_names( ) {
						static auto names = []( ) {
							std::vector<std::string> result;
							result.push_back( "cos" );
							result.push_back( "root" );
							result.push_back( "sin" );
							result.push_back( "tan" );
							std::sort( result.begin( ), result.end( ) );
							return result;
						}( );
						return names;
					}

					template<typename Iterator>
					auto is_function( Iterator pos, Iterator end_pos ) {
						auto result = parser_result( false, pos, end_pos );	
						

						return result;
					}

					template<typename Iterator>
					parser_result_t<Iterator> is_function( Iterator pos, Iterator end_pos ) {
						auto result = parser_result( false, pos, end_pos );	


					}



				};
			}	// namespace anonymous
		}	// namespace impl

		template<typename Iterator>
		struct mismatched_bracket {
			std::pair<Iterator, Iterator> positions;
			mismatched_bracket( Iterator first, Iterator second ): positions{ std::make_pair( first, second ) } { }
		};

		template<typename Iterator>
		auto make_mismatched_bracket_exception( Iterator first, Iterator second ) {
			return mismatched_bracket<Iterator>{ first, second };
		}

		std::unique_ptr<ast::expression> evaluation( boost::string_ref char_stream ) {
			std::unique_ptr<ast::expression> result;
			std::vector<decltype(char_stream.begin( ))> bracket_stack;

			auto pos = char_stream.begin( );
			while( pos != char_stream.end( ) ) {
				switch( *pos ) {
					case ' ': break;
					case '	': break;
					case '\n': break;
					case '(': 
					case '{':
					case '[':
						bracket_stack.push_back( pos );
					break;
					case ')':
						if( *bracket_stack.front( ) != '(' ) {
							throw make_mismatched_bracket_exception( bracket_stack.front( ), pos );
						}
						bracket_stack.pop_back( );
					break;
					case '}':
						if( *bracket_stack.front( ) != '{' ) {
							throw make_mismatched_bracket_exception( bracket_stack.front( ), pos );
						}
						bracket_stack.pop_back( );
					break;
					case ']':
						if( *bracket_stack.front( ) != '[' ) {
							throw make_mismatched_bracket_exception( bracket_stack.front( ), pos );
						}
						bracket_stack.pop_back( );
					break;

				}
				++pos;
			}
			return result;
		}
	}	// namespace expression_parser
}	// namespace daw

