/*
 * EmmaParser.cpp
 *
 *  Created on: 15 ott 2015
 *      Author: dariux881
 */

#include "EmmaParser.h"
#include <iostream>

map<string, Grammar*> EmmaParser::allGrammars;
map<string, Model*> EmmaParser::allModels;
map<string, Interpretation*> EmmaParser::allInterpretations;
vector<Interpretation*>	EmmaParser::tmpInterpretationRef;
vector<Container*>		EmmaParser::tmpContainerRef;

EmmaParser::EmmaParser() {
}

EmmaParser::~EmmaParser() {
}

/**
 * This method parses a xml emma, store in a file.
 */
Emma* EmmaParser::parseDocument(string path) {
	Emma* node = NULL;
	xmlNode *root_element = NULL;

	xmlDoc *doc = xmlReadFile(path.c_str(), NULL, 0);
	if( !doc ) {
		return NULL;
	}

	root_element = xmlDocGetRootElement(doc);
	if( !root_element )
		return NULL;

	if( !xmlStrcmp(root_element->name, (const xmlChar*)"emma")) {
		node = readEmma(root_element->children);
	}

	return node;
}

/**
 * This method parses a xml emma, stored in a string.
 */
Emma* EmmaParser::parseNode(string emmaCode) {
	Emma* node = NULL;
	xmlNode *root_element = NULL;

	xmlDoc *doc = xmlParseDoc((const xmlChar*)emmaCode.c_str());
	if( !doc ) {
		return NULL;
	}

	root_element = xmlDocGetRootElement(doc);
	if( !root_element )
		return NULL;

	if( !xmlStrcmp(root_element->name, (const xmlChar*)"emma")) {
		node = readEmma(root_element->children);
	}

	return node;
}

/**
 * It reads an emma node
 */
Emma* EmmaParser::readEmma(xmlNode* node) {
	Emma* result;
	xmlNode *curNode = NULL;
	Container* cont = NULL;
	Interpretation* inter = NULL;

	result = new Emma;

	for( curNode=node; curNode; curNode=curNode->next) {
		if( !xmlStrcmp(curNode->name, (const xmlChar*)"interpretation") ) {

			if( cont ) {
				// I found an interpretation node with an already created default container. Error
				delete cont;
				cont = NULL;
				break;
			}

			cont = new OneOf;
			inter = readInterpretation(curNode);

			if( !inter ) {
				// The child node "interpretation" is not valid
				delete cont;
				cont = NULL;
				break;
			}

			inter->setContainerParent(cont);
			cont->addInterpretation(inter);
			cont->finalizeCreation();
			result->setContainer(cont);
		}
		else if( !xmlStrcmp(curNode->name, (const xmlChar*)"one-of") ) {
			cont = readContainer(curNode, "one-of");

			if( cont ) {
				if( result->getContainer() ) {
					// I found a valid container, but the node already has one of them. Error
					delete cont;
					cont = NULL;
					break;
				}
				else {
					result->setContainer(cont);
				}
			}
		}
		else if( !xmlStrcmp(curNode->name, (const xmlChar*)"group") ) {
			cont = readContainer(curNode, "group");

			if( cont ) {
				if( result->getContainer() ) {
					// I found a valid container, but the node already has one of them. Error
					delete cont;
					cont = NULL;
					break;
				}
				else {
					result->setContainer(cont);
				}
			}
		}
		else if( !xmlStrcmp(curNode->name, (const xmlChar*)"sequence") ) {
			cont = readContainer(curNode, "sequence");

			if( cont ) {
				if(result->getContainer() ) {
					// I found a valid container, but the node already has one of them. Error
					delete cont;
					cont = NULL;
					break;
				}
				else {
					result->setContainer(cont);
				}
			}
		}
		else if( !xmlStrcmp(curNode->name, (const xmlChar*)"grammar") ) {
			Grammar* gram = readGrammar(curNode);

			if( gram )
				allGrammars[gram->getId()] = gram;
		}
		else if( !xmlStrcmp(curNode->name, (const xmlChar*)"model") ) {
			Model* model = readModel(curNode);

			if( model )
				allModels[model->getId()] = model;
		}
		else if( !xmlStrcmp(curNode->name, (const xmlChar*)"derivation") ) {
			Derivation* deriv = readDerivation(curNode);

			if( deriv && !result->getDerivation() ) {
				result->setDerivation(deriv);
			}
			else {
				delete deriv;
				deriv = NULL;
			}
		}
	}

	if( !inter && !cont) {
		delete result;
		result = NULL;
	}

	finalize();

	return result;
}

/**
 * This method read a container, considering the different types of them
 */
Container* EmmaParser::readContainer(xmlNode* node, string type) {
	Container*	cont = NULL;
	xmlAttr*	prop = NULL;
	xmlNode*	curNode = NULL;
	string		propStr;
	bool		error = false;

	if (!type.compare("one-of")) {
		cont = new OneOf;
	}
	else if (!type.compare("group")) {
		cont = new Group;
	}
	else if (!type.compare("sequence")) {
		cont = new Sequence;
	}
	prop = node->properties;

	// I iterates on the attributes
	while(prop && prop->name && prop->children) {
		propStr = string((const char*)xmlNodeListGetString(node->doc, prop->children, 1));

		if( !xmlStrcmp(prop->name, (const xmlChar*)"id")) {
			cont->setId( propStr );
		}
		else if( !xmlStrcmp(prop->name, (const xmlChar*)"medium")) {
			cont->setMedium( propStr );
		}
		else if( !xmlStrcmp(prop->name, (const xmlChar*)"mode")) {
			cont->setMode( propStr );
		}
		else if( !xmlStrcmp(prop->name, (const xmlChar*)"tokens")) {
			cont->setTokens( propStr );
		}
		else if( !xmlStrcmp(prop->name, (const xmlChar*)"confidence")) {
			cont->setConfidence( Utils::stringToNumber<float>( propStr ) );
		}
		else if( !xmlStrcmp(prop->name, (const xmlChar*)"duration")) {
			cont->setDuration( Utils::stringToNumber<unsigned long>( propStr ) );
		}
		else if( !xmlStrcmp(prop->name, (const xmlChar*)"start")) {
			cont->setStart( Utils::stringToNumber<unsigned long long>( propStr ) );
		}
		else if( !xmlStrcmp(prop->name, (const xmlChar*)"end")) {
			cont->setEnd( Utils::stringToNumber<unsigned long long>( propStr ) );
		}
		else if( !xmlStrcmp(prop->name, (const xmlChar*)"verbal")) {
			cont->setVerbal( propStr.compare("true")==0 ? true : false );
		}
		else if( !xmlStrcmp(prop->name, (const xmlChar*)"signal-size")) {
			cont->setSignalSize( Utils::stringToNumber<unsigned long long>( propStr ) );
		}
		else if( !xmlStrcmp(prop->name, (const xmlChar*)"offset-to-start")) {
			cont->setOffsetToStart( Utils::stringToNumber<long>( propStr ) );
		}
		else if( !xmlStrcmp(prop->name, (const xmlChar*)"cost")) {
			cont->setCost( Utils::stringToNumber<float>( propStr ) );
		}
		else if( !xmlStrcmp(prop->name, (const xmlChar*)"process")) {
			cont->setProcess( propStr );
		}
		else if( !xmlStrcmp(prop->name, (const xmlChar*)"lang")) {
			cont->setLang( propStr );
		}
		else if( !xmlStrcmp(prop->name, (const xmlChar*)"signal")) {
			cont->setSignal( propStr );
		}
		else if( !xmlStrcmp(prop->name, (const xmlChar*)"source")) {
			cont->setSource( propStr );
		}
		else if( !xmlStrcmp(prop->name, (const xmlChar*)"function")) {
			cont->setFunction( propStr );
		}
		else if( !xmlStrcmp(prop->name, (const xmlChar*)"dialog-turn")) {
			cont->setDialogTurn( propStr );
		}
		else if( !xmlStrcmp(prop->name, (const xmlChar*)"media-type")) {
			cont->setMediaType( propStr );
		}
		else if( !xmlStrcmp(prop->name, (const xmlChar*)"model-ref")) {
			cont->setModelRef( propStr );
		}
		else if( !xmlStrcmp(prop->name, (const xmlChar*)"grammar-ref")) {
			cont->setGrammarRef( propStr );
		}
		else if( !xmlStrcmp(prop->name, (const xmlChar*)"time-ref-uri")) {
			cont->setTimeRefUri( propStr );
		}
		else if( !xmlStrcmp(prop->name, (const xmlChar*)"time-ref-anchor-point")) {
			cont->setTimeRefAnchorPoint( propStr );
		}
		else if( (!xmlStrcmp(prop->name, (const xmlChar*)"disjunction-type")) &&
				( !type.compare("one-of") )) {

			if( !propStr.compare("recognition") )
				((OneOf*)cont)->setDisjunctionType( RECOGNITION );
			else if( !propStr.compare("understanding") )
				((OneOf*)cont)->setDisjunctionType( UNDERSTANDING );
			else if( !propStr.compare("multi-device") )
				((OneOf*)cont)->setDisjunctionType( MULTI_DEVICE );
			else if( !propStr.compare("multi-process") )
				((OneOf*)cont)->setDisjunctionType( MULTI_PROCESS );

		}

		prop = prop->next;
	}

	if( error ) {
		cerr << "an error occurred in readContainer - parsing attributes" << endl;
		// An error occurred
		delete cont;
		return NULL;
	}

	// I analyze all the children
	for( curNode=node->children; curNode; curNode=curNode->next ) {

		if( !xmlStrcmp(curNode->name, (const xmlChar*)"interpretation" ) ) {
			Interpretation* newInter;

			newInter = readInterpretation(curNode);

			if( !newInter ) {
				// An error occured by analyzing children
				cerr << "An error occured by analyzing children" << endl;
				error = true;
				break;
			}

			newInter->setContainerParent( cont);
			cont->addInterpretation(  newInter );
		}
		else if( !xmlStrcmp(curNode->name, (const xmlChar*)"one-of" ) ) {
			Container* newCont;

			newCont = readContainer(curNode, "one-of");
			if( !newCont ) {
				// An error occured by analyzing children
				error = true;
				break;
			}

			cont->addNestedContainer( newCont );
			newCont->setParentContainer(cont);
		}
		if( !xmlStrcmp(curNode->name, (const xmlChar*)"group" ) ) {
			Container* newCont;

			newCont = readContainer(curNode, "group");
			if( !newCont ) {
				// An error occured by analyzing children
				error = true;
				break;
			}

			cont->addNestedContainer( newCont );
			newCont->setParentContainer( cont);
		}
		if( !xmlStrcmp(curNode->name, (const xmlChar*)"sequence" ) ) {
			Container* newCont;

			newCont = readContainer(curNode, "sequence");
			if( !newCont ) {
				// An error occured by analyzing children
				error = true;
				break;
			}

			cont->addNestedContainer( newCont );
			newCont->setParentContainer( cont);
		}
	}

	if( error ) {
		// An error occurred
		delete cont;
		return NULL;
	}

	cont->finalizeCreation();
	tmpContainerRef.push_back( cont );

	return cont;
}

/**
 * It reads an interpretation node
 */
Interpretation* EmmaParser::readInterpretation(xmlNode* node) {
	Interpretation* inter = NULL;
	xmlAttr*	prop = NULL;
	string		propStr;
	bool		error = false;
	xmlNode*	curNode;

	inter = new Interpretation;
	prop = node->properties;

	// I iterates on the attributes
	while(prop && prop->name && prop->children) {
		propStr = string((const char*)xmlNodeListGetString(node->doc, prop->children, 1));

		if( !xmlStrcmp(prop->name, (const xmlChar*)"id")) {
			inter->setId( propStr );
		}
		else if( !xmlStrcmp(prop->name, (const xmlChar*)"medium")) {
			inter->setMedium(propStr );
		}
		else if( !xmlStrcmp(prop->name, (const xmlChar*)"mode")) {
			inter->setMode(propStr );
		}
		else if( !xmlStrcmp(prop->name, (const xmlChar*)"tokens")) {
			inter->setTokens(propStr );
		}
		else if( !xmlStrcmp(prop->name, (const xmlChar*)"confidence")) {
			inter->setConfidence(Utils::stringToNumber<float>( propStr ) );
		}
		else if( !xmlStrcmp(prop->name, (const xmlChar*)"duration")) {
			inter->setDuration(Utils::stringToNumber<unsigned long>( propStr ) );
		}
		else if( !xmlStrcmp(prop->name, (const xmlChar*)"start")) {
			inter->setStart(Utils::stringToNumber<unsigned long long>( propStr ) );
		}
		else if( !xmlStrcmp(prop->name, (const xmlChar*)"end")) {
			inter->setEnd(Utils::stringToNumber<unsigned long long>( propStr ) );
		}
		else if( !xmlStrcmp(prop->name, (const xmlChar*)"no-input")) {
			inter->setNoInput(propStr.compare("true")==0 ? true : false );
		}
		else if( !xmlStrcmp(prop->name, (const xmlChar*)"uninterpreted")) {
			inter->setUninterpreted(propStr.compare("true")==0 ? true : false );
		}
		else if( !xmlStrcmp(prop->name, (const xmlChar*)"verbal")) {
			inter->setVerbal(propStr.compare("true")==0 ? true : false );
		}
		else if( !xmlStrcmp(prop->name, (const xmlChar*)"singnal-size")) {
			inter->setSignalSize(Utils::stringToNumber<unsigned long long>( propStr ) );
		}
		else if( !xmlStrcmp(prop->name, (const xmlChar*)"offset-to-start")) {
			inter->setOffsetToStart(Utils::stringToNumber<long>( propStr ) );
		}
		else if( !xmlStrcmp(prop->name, (const xmlChar*)"cost")) {
			inter->setCost(Utils::stringToNumber<float>( propStr ) );
		}
		else if( !xmlStrcmp(prop->name, (const xmlChar*)"process")) {
			inter->setProcess(propStr );
		}
		else if( !xmlStrcmp(prop->name, (const xmlChar*)"lang")) {
			inter->setLang(propStr );
		}
		else if( !xmlStrcmp(prop->name, (const xmlChar*)"signal")) {
			inter->setSignal(propStr );
		}
		else if( !xmlStrcmp(prop->name, (const xmlChar*)"source")) {
			inter->setSource(propStr );
		}
		else if( !xmlStrcmp(prop->name, (const xmlChar*)"function")) {
			inter->setFunction(propStr );
		}
		else if( !xmlStrcmp(prop->name, (const xmlChar*)"dialog-turn")) {
			inter->setDialogTurn(propStr );
		}
		else if( !xmlStrcmp(prop->name, (const xmlChar*)"media-type")) {
			inter->setMediaType(propStr );
		}
		else if( !xmlStrcmp(prop->name, (const xmlChar*)"model-ref")) {
			inter->setModelRef(propStr );
		}
		else if( !xmlStrcmp(prop->name, (const xmlChar*)"grammar-ref")) {
			inter->setGrammarRef(propStr );
		}
		else if( !xmlStrcmp(prop->name, (const xmlChar*)"time-ref-uri")) {
			inter->setTimeRefUri(propStr );
		}
		else if( !xmlStrcmp(prop->name, (const xmlChar*)"time-ref-anchor-point")) {
			inter->setTimeRefAnchorPoint(propStr );
		}

		prop = prop->next;
	}

	if( error ) {
		// An error occurred
		delete inter;
		return NULL;
	}

	for( curNode=node->children; curNode; curNode=curNode->next ) {
		if( !xmlStrcmp(curNode->name, (const xmlChar*)"derived-from" ) ) {
			DerivedFrom* df = readDerivedFrom(curNode);

			if( df )
				inter->addDerivedFrom(df);
		}
	}

	tmpInterpretationRef.push_back(inter);
	allInterpretations[inter->getId()] = inter;

	return inter;
}

/**
 * Parses a derivation node
 */
Derivation* EmmaParser::readDerivation(xmlNode* node) {
	Derivation* der;
	xmlNode*	curNode;

	der = new Derivation;
	for( curNode=node->children; curNode; curNode=curNode->next ) {
		if( !xmlStrcmp(curNode->name, (const xmlChar*)"interpretation" ) ) {
			Interpretation *newInt;
			newInt = readInterpretation(curNode);

			if( newInt ) {
				der->addInterpretation(newInt);
			}
		}
		else if( !xmlStrcmp(curNode->name, (const xmlChar*)"one-of" ) ) {
			Container* cont;
			cont = readContainer(curNode, "one-of");

			if( cont ) {
				der->addContainer(cont);
			}
		}
		else if( !xmlStrcmp(curNode->name, (const xmlChar*)"group" ) ) {
			Container* cont;
			cont = readContainer(curNode, "group");

			if( cont ) {
				der->addContainer(cont);
			}
		}
		else if( !xmlStrcmp(curNode->name, (const xmlChar*)"sequence" ) ) {
			Container* cont;
			cont = readContainer(curNode, "sequence");

			if( cont ) {
				der->addContainer(cont);
			}
		}
	}

	return der;
}

DerivedFrom* EmmaParser::readDerivedFrom(xmlNode* node) {
	DerivedFrom* 	df = new DerivedFrom;
	xmlAttr*		prop;
	string			propStr;

	prop = node->properties;

	// I iterates on the attributes
	while(prop && prop->name && prop->children) {
		propStr = string((const char*)xmlNodeListGetString(node->doc, prop->children, 1));

		if( !xmlStrcmp(prop->name, (const xmlChar*)"resource")) {
			df->setResourceId( propStr );
		}
		else if( !xmlStrcmp(prop->name, (const xmlChar*)"composite")) {
			df->setComposite( propStr.compare("true")==0 ? true : false );
		}

		prop = prop->next;
	}

	return df;
}

/**
 * It parses a node with a grammar specification
 */
Grammar* EmmaParser::readGrammar(xmlNode* node) {
	Grammar* 	gram;
	xmlAttr*	prop = NULL;
	string		propStr;

	gram = new Grammar;
	prop = node->properties;

	// I iterates on the attributes
	while(prop && prop->name && prop->children) {
		propStr = string((const char*)xmlNodeListGetString(node->doc, prop->children, 1));

		if( !xmlStrcmp(prop->name, (const xmlChar*)"id")) {
			gram->setId( propStr );
		}
		else if( !xmlStrcmp(prop->name, (const xmlChar*)"ref")) {
			gram->setUri( propStr );
		}
	}

	return gram;
}

/**
 * It parses a node with a model specification
 */
Model* EmmaParser::readModel(xmlNode* node) {
	Model* 		mod;
	xmlAttr*	prop = NULL;
	string		propStr;

	mod = new Model;
	prop = node->properties;

	// I iterates on the attributes
	while(prop && prop->name && prop->children) {
		propStr = string((const char*)xmlNodeListGetString(node->doc, prop->children, 1));

		if( !xmlStrcmp(prop->name, (const xmlChar*)"id")) {
			mod->setId( propStr );
		}
		else if( !xmlStrcmp(prop->name, (const xmlChar*)"ref")) {
			mod->setUri( propStr );
		}
	}

	return mod;
}

/**
 * It returns a reference to a grammar in the code
 */
Grammar* EmmaParser::getGrammarRef(string id) {
	map<string, Grammar*>::iterator it;

	it = allGrammars.find(id);
	if( it==allGrammars.end() )
		return NULL;

	return it->second;
}

/**
 * It returns a reference to a model in the code
 */
Model* EmmaParser::getModelRef(string id) {
	map<string, Model*>::iterator it;

	it = allModels.find(id);
	if( it==allModels.end() )
		return NULL;

	return it->second;
}

/**
 * It completes internal structures
 */
void EmmaParser::finalize() {
	vector<Interpretation*> inter;
	vector<Interpretation*>::iterator intIt;
	vector<Container*>::iterator conIt;
	vector<DerivedFrom*> df;
	vector<DerivedFrom*>::iterator dfIt;
	Interpretation*	tmpIntRef;
	string tmpId;

	// I complete the interpretation binding
	for( intIt=tmpInterpretationRef.begin(); intIt!=tmpInterpretationRef.end(); intIt++) {
		// I link grammars id and objects
		tmpId = (*intIt)->getGrammarRefId();

		if( (tmpId.compare("")) &&// valid stored id
				( allGrammars.find(tmpId)!=allGrammars.end() ) ) { // found

			(*intIt)->setGrammarRef( allGrammars[tmpId] );
		}

		// I link models id and objects
		tmpId = (*intIt)->getModelRefId();

		if( (tmpId.compare("")) && // valid stored id
				( allModels.find(tmpId)==allModels.end() ) ) { // found

			(*intIt)->setModelRef( allModels[tmpId] );
		}

		// I link interpretations and derived-from objects
		df = (*intIt)->getDerivedFrom();
		for( dfIt=df.begin(); dfIt!=df.end(); dfIt++ ) {
			tmpIntRef = allInterpretations[ (*dfIt)->getResourceId() ];
			if( tmpIntRef )
				(*dfIt)->setResource( tmpIntRef);
		}
	}

	// I complete the container binding
	for( conIt=tmpContainerRef.begin(); conIt!=tmpContainerRef.end(); conIt++) {
		// I link grammars id and objects
		tmpId = (*conIt)->getGrammarRefId();

		if( (tmpId.compare("")) &&// valid stored id
				( allGrammars.find(tmpId)!=allGrammars.end() ) ) { // found

			(*conIt)->setGrammarRef(allGrammars[tmpId] );
		}

		// I link models id and objects
		tmpId = (*conIt)->getModelRefId();

		if( (tmpId.compare("")) && // valid stored id
				( allModels.find(tmpId)==allModels.end() ) ) { // found

			(*conIt)->setModelRef( allModels[tmpId] );
		}

		// I link containers and derived-from objects
		df = (*conIt)->getDerivedFrom();
		for( dfIt=df.begin(); dfIt!=df.end(); dfIt++ ) {
			tmpIntRef = allInterpretations[ (*dfIt)->getResourceId() ];
			if( tmpIntRef )
				(*dfIt)->setResource( tmpIntRef);
		}

		// I link interpretations nested in a container
		inter = (*conIt)->getInterpretations();
		for( intIt=inter.begin(); intIt!=inter.end(); intIt++) {
			df = (*intIt)->getDerivedFrom();
			for( dfIt=df.begin(); dfIt!=df.end(); dfIt++ ) {
				tmpIntRef = allInterpretations[ (*dfIt)->getResourceId() ];
				if( tmpIntRef )
					(*dfIt)->setResource( tmpIntRef);
			}
		}
	}

	allGrammars.clear();
	allModels.clear();
	allInterpretations.clear();
	tmpContainerRef.clear();
	tmpInterpretationRef.clear();
}

