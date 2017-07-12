/*
 * EmmaParser.h
 *
 *  Created on: 15 ott 2015
 *      Author: dariux881
 */

#ifndef EMMAPARSER_H_
#define EMMAPARSER_H_

#ifdef EMMAPARSER_EXPORTS  
#define EMMAPARSER_API __declspec(dllexport)   
#else  
#define EMMAPARSER_API __declspec(dllimport)   
#endif  

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
	EMMAPARSER_API EmmaParser();
	EMMAPARSER_API virtual ~EmmaParser();

	static EMMAPARSER_API Emma* parseDocument(string path);
	static EMMAPARSER_API Emma* parseNode(string node);

	Grammar*	getGrammarRef(string id);
	Model*		getModelRef(string id);

	static map<string, Grammar*>	allGrammars;
	static map<string, Model*>		allModels;
	static map<string, Interpretation*> allInterpretations;

private:
	static Emma* 			readEmma(xmlNode*);
	static Container* 		readContainer(xmlNode*, string);
	static Interpretation* readInterpretation(xmlNode*);
	static Derivation*		readDerivation(xmlNode*);
	static DerivedFrom*	readDerivedFrom(xmlNode*);
	static Grammar*		readGrammar(xmlNode*);
	static Model*			readModel(xmlNode*);

	static void	finalize();

	static vector<Interpretation*>	tmpInterpretationRef;
	static vector<Container*>		tmpContainerRef;
};

#endif /* EMMAPARSER_H_ */
