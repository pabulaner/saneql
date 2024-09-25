PREFIX:=bin/

all: $(PREFIX)saneql

src:=parser/ASTBase.cpp parser/SaneQLLexer.cpp infra/Schema.cpp semana/Functions.cpp semana/SemanticAnalysis.cpp algebra/Expression.cpp algebra/Operator.cpp sql/SQLWriter.cpp adapter/StringUtil.cpp adapter/ConditionUtil.cpp adapter/OperatorUtil.cpp adapter/TimeUtil.cpp adapter/Optimizer.cpp adapter/IUSet.cpp adapter/CppWriter.cpp adapter/CppCompiler.cpp main.cpp
qsrc:=adapter/StringUtil.cpp adapter/TimeUtil.cpp adapter/Database.cpp
gensrc:=$(PREFIX)parser/saneql_parser.cpp
obj:=$(addprefix $(PREFIX),$(src:.cpp=.o)) $(gensrc:.cpp=.o)

CXXFLAGS:=-std=c++23 -I$(PREFIX) -I. -Wall -Wextra -mavx2 -w -O3

-include $(addprefix $(PREFIX),$(src:.cpp=.d)) $(gensrc:.cpp=.d)

checkdir=@mkdir -p $(dir $@)
ASTGEN:=$(PREFIX)astgen --astbaseheader parser/ASTBase.hpp --astbaseclass saneql::ASTBase --astheader parser/AST.hpp --namespace saneql::ast

$(PREFIX)parser/AST.hpp: parser/astspec $(PREFIX)astgen
	$(checkdir)
	$(ASTGEN) astheader parser/astspec $@

$(PREFIX)parser/AST.cpp: parser/astspec $(PREFIX)astgen
	$(checkdir)
	$(ASTGEN) astbody parser/astspec $@

$(PREFIX)parser/AST.o: $(PREFIX)parser/AST.hpp
$(PREFIX)parser/AST.d: $(PREFIX)parser/AST.cpp

$(PREFIX)parser/saneql.expanded.ypp: parser/astspec parser/saneql.ypp $(PREFIX)astgen
	@mkdir -p $(dir $@)
	$(ASTGEN) expandgrammar parser/astspec parser/saneql.ypp $@

$(PREFIX)parser/saneql_parser.o: $(PREFIX)parser/AST.hpp
$(PREFIX)parser/saneql_parser.cpp: $(PREFIX)parser/saneql.expanded.ypp
	makeutil/patchbison `which bison` $< $@

$(PREFIX)semana/SemanticAnalysis.o: $(PREFIX)parser/AST.hpp

CXX?=g++
compilecpp=$(CXX) -c -o$@ $(strip $(CXXFLAGS) $(CXXFLAGS-$(dir $<)) $(CXXFLAGS-$<) $(IFLAGS) $(LLVM_IFLAGS)) -MMD -MP -MF $(@:.o=.d) $<

$(PREFIX)%.o: %.cpp
	$(checkdir)
	$(compilecpp)

$(PREFIX)%.o: $(PREFIX)%.cpp
	$(checkdir)
	$(compilecpp)

$(PREFIX)saneql: $(obj)
	$(CXX) $(CXXFLAGS) -o$@ $^ -lfmt 

$(PREFIX)astgen: $(PREFIX)makeutil/astgen.o
	$(CXX) $(CXXFLAGS) -o$@ $^

# compile
cquery:
	./bin/saneql ./query/benchmark/*.sane > ./adapter/resource/query.hpp
	$(CXX) $(CXXFLAGS) $(qsrc) -laio -o ./bin/query

# run
rquery:
	./setup.sh
	./bin/query

# compile and run
crquery:
	make cquery rquery