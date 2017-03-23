/*
 * Container.h
 *
 *  Created on: 15 ott 2015
 *      Author: dariux881
 */

#ifndef CONTAINER_CONTAINER_H_
#define CONTAINER_CONTAINER_H_

#include <vector>
#include "../Interpretation.h"
#include "../Grammar.h"
#include "../Model.h"
#include "../DerivedFrom.h"
#include <string>
#include <iostream>

using namespace std;

enum ContainerType {ONE_OF, GROUP, SEQUENCE};

class Interpretation;
class DerivedFrom;

class Container {
public:
	Container();
	virtual ~Container();

	void setContainerType(ContainerType val) { containerType = val; }
	void setId(string id) {this->id = id;}
	void setMedium(string medium) {this->medium = medium;}
	void setMode(string mode) {this->mode = mode;}
	void setTokens(string tokens) {this->tokens = tokens;}
	void setConfidence(float confidence) { this->confidence = confidence; }
	void setStart(unsigned long long start);
	void setDuration(unsigned long long duration);
	void setEnd(unsigned long long end);
	void setParentContainer(Container* parentContainer) { this->parentContainer = parentContainer; }
	void setCost(float cost) { this->cost = cost; }
	void setDialogTurn(string dialogTurn) { dialog_turn = dialogTurn; }
	void setFunction(string function) { this->function = function; }
	void setGrammarRef(string grammarRef) { grammar_ref = grammarRef; }
	void setGrammarRef(Grammar* grammarRef) { this->grammarRef = grammarRef; }
	void setLang(string lang) { this->lang = lang; }
	void setMediaType(string mediaType) { media_type = mediaType; }
	void setModelRef(string modelRef) { model_ref = modelRef; }
	void setModelRef(Model* modelRef) { this->modelRef = modelRef; }
	void setOffsetToStart(long offsetToStart) { offset_to_start = offsetToStart; }
	void setProcess(string process) { this->process = process; }
	void setSignal(string signal) { this->signal = signal; }
	void setSignalSize(unsigned long long signalSize) { signal_size = signalSize; }
	void setSource(string source) { this->source = source; }
	void setTimeRefAnchorPoint(string timeRefAnchorPoint) { time_ref_anchor_point = timeRefAnchorPoint; }
	void setTimeRefUri(string timeRefUri) { time_ref_uri = timeRefUri; }
	void setVerbal(bool verbal) { this->verbal = verbal; }
	void addDerivedFrom(DerivedFrom* derivedFrom);

	float 			getConfidence() { return confidence; }
	unsigned long long 	getDuration() { return (end-start); }
	unsigned long long	getEnd() { return end; }
	const string&	getId() { return id; }
	const string&	getMedium() { return medium; }
	const string&	getMode() { return mode; }
	unsigned long long	getStart() { return start; }
	const string&	getTokens() { return tokens; }
	ContainerType	getContainerType() { return containerType; }
	Container* 		getParentContainer() { return parentContainer; }
	float 			getCost() { return cost; }
	string 			getDialogTurn() { return dialog_turn; }
	string 			getFunction() { return function; }
	string 			getGrammarRefId() { return grammar_ref; }
	Grammar* 		getGrammarRef() { return grammarRef; }
	string 			getLang() { return lang; }
	string 			getMediaType() { return media_type; }
	string 			getModelRefId() { return model_ref; }
	Model* 			getModelRef() { return modelRef; }
	long 			getOffsetToStart() { return offset_to_start; }
	string 			getProcess() { return process; }
	string 			getSignal() { return signal; }
	unsigned long long 	getSignalSize() { return signal_size; }
	string 			getSource() { return source; }
	string 			getTimeRefAnchorPoint() { return time_ref_anchor_point; }
	string 			getTimeRefUri() { return time_ref_uri; }
	bool 			isVerbal() { return verbal; }
	vector<DerivedFrom*> 	getDerivedFrom() { return derivedFrom; }
	vector<Container*>		getNested() { return nested; }

	void			finalizeCreation();

	virtual void addInterpretation(Interpretation* newInt) =0;
	virtual void addNestedContainer(Container* newCont) =0;
	virtual vector<Interpretation*> getInterpretations() =0;
	virtual string toString() =0;

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
