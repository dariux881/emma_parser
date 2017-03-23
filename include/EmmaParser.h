/*
 * EmmaParser.h
 *
 *  Created on: 15 ott 2015
 *      Author: dariux881
 */

#ifndef EMMAPARSER_H_
#define EMMAPARSER_H_

#include "Emma.h"
#include "Container/Container.h"
#include "Container/OneOf.h"
#include "Container/Group.h"
#include "Container/Sequence.h"
#include "Interpretation.h"
#include "Utils/Utils.h"
#include "Grammar.h"
#include "Model.h"
#include "Derivation.h"
#include "DerivedFrom.h"
#include <map>
#include <string>

#include <libxml/tree.h>
#include <libxml/parser.h>

using namespace std;

class EmmaParser {
public:
	EmmaParser();
	virtual ~EmmaParser();

	Emma* parseDocument(string path);
	Emma* parseNode(string node);

	Grammar*	getGrammarRef(string id);
	Model*		getModelRef(string id);

	static map<string, Grammar*>	allGrammars;
	static map<string, Model*>		allModels;
	static map<string, Interpretation*> allInterpretations;

private:
	Emma* 			readEmma(xmlNode*);
	Container* 		readContainer(xmlNode*, string);
	Interpretation* readInterpretation(xmlNode*);
	Derivation*		readDerivation(xmlNode*);
	DerivedFrom*	readDerivedFrom(xmlNode*);
	Grammar*		readGrammar(xmlNode*);
	Model*			readModel(xmlNode*);

	void	finalize();

	vector<Interpretation*>	tmpInterpretationRef;
	vector<Container*>		tmpContainerRef;
};

#endif /* EMMAPARSER_H_ */
