/*
 * Container.h
 *
 *  Created on: 15 ott 2015
 *      Author: dariux881
 */

#ifndef CONTAINER_CONTAINER_H_
#define CONTAINER_CONTAINER_H_

#include "../../config.h"
#include <vector>
#include "../Interpretation.h"
#include "../Grammar.h"
#include "../Model.h"
#include "../DerivedFrom.h"
#include <string>
#include <iostream>

using namespace std;

enum ContainerType {ONE_OF_CONTAINER, GROUP_CONTAINER, SEQUENCE_CONTAINER};

class Interpretation;
class DerivedFrom;

class Container {
public:
	EMMAPARSER_API Container();
	EMMAPARSER_API virtual ~Container();

	EMMAPARSER_API void setContainerType(ContainerType val) { this->containerType = val; }
	EMMAPARSER_API void setId(string newId) { this->id = newId;}
	EMMAPARSER_API void setMedium(string medium2) { this->medium = medium2;}
	EMMAPARSER_API void setMode(string mode2) { this->mode = mode2;}
	EMMAPARSER_API void setTokens(string tokens2) { this->tokens = tokens2;}
	EMMAPARSER_API void setConfidence(float confidence2) { this->confidence = confidence2; }
	EMMAPARSER_API void setStart(unsigned long long start);
	EMMAPARSER_API void setDuration(unsigned long long duration);
	EMMAPARSER_API void setEnd(unsigned long long end);
	EMMAPARSER_API void setParentContainer(Container* parentContainer2) { this->parentContainer = parentContainer2; }
	EMMAPARSER_API void setCost(float cost2) { this->cost = cost2; }
	EMMAPARSER_API void setDialogTurn(string dialogTurn) { this->dialog_turn = dialogTurn; }
	EMMAPARSER_API void setFunction(string function2) { this->function = function2; }
	EMMAPARSER_API void setGrammarRef(string grammarRef) { this->grammar_ref = grammarRef; }
	EMMAPARSER_API void setGrammarRef(Grammar* grammarRef) { this->grammarRef = grammarRef; }
	EMMAPARSER_API void setLang(string lang) { this->lang = lang; }
	EMMAPARSER_API void setMediaType(string mediaType) { this->media_type = mediaType; }
	EMMAPARSER_API void setModelRef(string modelRef) { this->model_ref = modelRef; }
	EMMAPARSER_API void setModelRef(Model* modelRef) { this->modelRef = modelRef; }
	EMMAPARSER_API void setOffsetToStart(long offsetToStart) { this->offset_to_start = offsetToStart; }
	EMMAPARSER_API void setProcess(string process2) { this->process = process2; }
	EMMAPARSER_API void setSignal(string signal2) { this->signal = signal2; }
	EMMAPARSER_API void setSignalSize(unsigned long long signalSize) { this->signal_size = signalSize; }
	EMMAPARSER_API void setSource(string source2) { this->source = source2; }
	EMMAPARSER_API void setTimeRefAnchorPoint(string timeRefAnchorPoint) { this->time_ref_anchor_point = timeRefAnchorPoint; }
	EMMAPARSER_API void setTimeRefUri(string timeRefUri) { this->time_ref_uri = timeRefUri; }
	EMMAPARSER_API void setVerbal(bool verbal) { this->verbal = verbal; }
	EMMAPARSER_API void addDerivedFrom(DerivedFrom* derivedFrom);

	EMMAPARSER_API float 			getConfidence() { return this->confidence; }
	EMMAPARSER_API unsigned long long 	getDuration() { return (this->end- this->start); }
	EMMAPARSER_API unsigned long long	getEnd() { return this->end; }
	EMMAPARSER_API const string&	getId() { return this->id; }
	EMMAPARSER_API const string&	getMedium() { return this->medium; }
	EMMAPARSER_API const string&	getMode() { return this->mode; }
	EMMAPARSER_API unsigned long long	getStart() { return this->start; }
	EMMAPARSER_API const string&	getTokens() { return this->tokens; }
	EMMAPARSER_API ContainerType	getContainerType() { return this->containerType; }
	EMMAPARSER_API Container* 		getParentContainer() { return this->parentContainer; }
	EMMAPARSER_API float 			getCost() { return this->cost; }
	EMMAPARSER_API string 			getDialogTurn() { return this->dialog_turn; }
	EMMAPARSER_API string 			getFunction() { return this->function; }
	EMMAPARSER_API string 			getGrammarRefId() { return this->grammar_ref; }
	EMMAPARSER_API Grammar* 		getGrammarRef() { return this->grammarRef; }
	EMMAPARSER_API string 			getLang() { return this->lang; }
	EMMAPARSER_API string 			getMediaType() { return this->media_type; }
	EMMAPARSER_API string 			getModelRefId() { return this->model_ref; }
	EMMAPARSER_API Model* 			getModelRef() { return this->modelRef; }
	EMMAPARSER_API long 			getOffsetToStart() { return this->offset_to_start; }
	EMMAPARSER_API string 			getProcess() { return this->process; }
	EMMAPARSER_API string 			getSignal() { return this->signal; }
	EMMAPARSER_API unsigned long long 	getSignalSize() { return this->signal_size; }
	EMMAPARSER_API string 			getSource() { return this->source; }
	EMMAPARSER_API string 			getTimeRefAnchorPoint() { return this->time_ref_anchor_point; }
	EMMAPARSER_API string 			getTimeRefUri() { return this->time_ref_uri; }
	EMMAPARSER_API bool 			isVerbal() { return this->verbal; }
	EMMAPARSER_API vector<DerivedFrom*> 	getDerivedFrom() { return this->derivedFrom; }
	EMMAPARSER_API vector<Container*>		getNested() { return this->nested; }

	EMMAPARSER_API void			finalizeCreation();

	virtual void addInterpretation(Interpretation* newInt) =0;
	virtual void addNestedContainer(Container* newCont) = 0;
	virtual vector<Interpretation*> getInterpretations() = 0;
	virtual string toString() = 0;

protected:
	string attributesToString();
	string childrenToString();

	string			id;
	unsigned long long	start, end, signal_size;
	long			offset_to_start;
	float 			confidence, cost;
	string			tokens, medium, mode;
	string			process, lang, signal, source, function, dialog_turn, media_type;
	string			model_ref, grammar_ref, time_ref_uri, time_ref_anchor_point;
	Grammar*		grammarRef;
	Model*			modelRef;
	bool			verbal;

	ContainerType 			containerType;
	Container*				parentContainer;
	vector<Interpretation*> interprets;
	vector<Container*>		nested;
	vector<DerivedFrom*>	derivedFrom;
};

#endif /* CONTAINER_CONTAINER_H_ */
