/*
 * Interpretation.h
 *
 *  Created on: 15 ott 2015
 *      Author: dariux881
 */

#ifndef INTERPRETATION_H_
#define INTERPRETATION_H_

#include "Container/Container.h"
#include "Grammar.h"
#include "Model.h"
#include "DerivedFrom.h"
#include <vector>
#include <string>

using namespace std;

class Container;

class Interpretation {
public:
	Interpretation();
	virtual ~Interpretation();

	void setId(string id) { this->id = id; }
	void setContainerParent(Container* par) { parent = par; }
	void setConfidence(float confidence) { this->confidence = confidence; }
	void setMedium(const string& medium) { this->medium = medium; }
	void setMode(const string& mode) { this->mode = mode; }
	void setNoInput(bool noInput) { no_input = noInput; }
	void setStart(unsigned long long start);
	void setDuration(unsigned long long duration);
	void setEnd(unsigned long long end);
	void setTokens(const string& tokens) { this->tokens = tokens; }
	void setUninterpreted(bool uninterpreted) { this->uninterpreted = uninterpreted; }
	void setCost(float cost) { this->cost = cost; }
	void setDialogTurn(string dialogTurn) { dialog_turn = dialogTurn; }
	void setFunction(string function) { this->function = function; }
	void setGrammarRef(string grammarRef) { grammar_ref = grammarRef; }
	void setLang(string lang) { this->lang = lang; }
	void setMediaType(string mediaType) { media_type = mediaType; }
	void setModelRef(string modelRef) { model_ref = modelRef; }
	void setOffsetToStart(long offsetToStart) { offset_to_start = offsetToStart; }
	void setProcess(string process) { this->process = process; }
	void setSignal(string signal) { this->signal = signal; }
	void setSignalSize(unsigned long long signalSize) { signal_size = signalSize; }
	void setSource(string source) { this->source = source; }
	void setTimeRefAnchorPoint(string timeRefAnchorPoint) { time_ref_anchor_point = timeRefAnchorPoint; }
	void setTimeRefUri(string timeRefUri) { time_ref_uri = timeRefUri; }
	void setVerbal(bool verbal) { this->verbal = verbal; }
	void setGrammarRef( Grammar* ref) { grammarRef = ref; }
	void setModelRef(Model* ref) { modelRef = ref; }
	void addDerivedFrom(DerivedFrom* derivedFrom);

	string			getId() { return id; }
	float 			getConfidence() { return confidence; }
	unsigned long long 	getDuration() { return (end-start); }
	unsigned long long 	getEnd() { return end; }
	const string& 	getMedium() { return medium; }
	const string& 	getMode() { return mode; }
	bool 			isNoInput() { return no_input; }
	Container* 		getParent() { return parent; }
	unsigned long long 	getStart() { return start; }
	const string& 	getTokens() { return tokens; }
	bool 			isUninterpreted() { return uninterpreted; }
	float 			getCost() { return cost; }
	string 			getDialogTurn() { return dialog_turn; }
	string 			getFunction() { return function; }
	string 			getLang() { return lang; }
	string 			getMediaType() { return media_type; }
	string 			getModelRefId() { return model_ref; }
	string	 		getGrammarRefId() { return grammar_ref; }
	Model* 			getModelRef() { return modelRef; }
	Grammar* 		getGrammarRef() { return grammarRef; }
	long 			getOffsetToStart() { return offset_to_start; }
	string 			getProcess() { return process; }
	string 			getSignal() { return signal; }
	unsigned long long 	getSignalSize() { return signal_size; }
	string 			getSource() { return source; }
	string 			getTimeRefAnchorPoint() { return time_ref_anchor_point; }
	string 			getTimeRefUri() { return time_ref_uri; }
	bool 			isVerbal() { return verbal; }
	vector<DerivedFrom*> getDerivedFrom() { return derivedFrom; }

	string 			toString();

private:
	string			attributesToString();

	string			id;
	unsigned long long 	start, end, signal_size;
	long			offset_to_start;
	float 			confidence, cost;
	string			tokens, medium, mode;
	string			process, lang, signal, source, function, dialog_turn, media_type;
	string			model_ref, grammar_ref, time_ref_uri, time_ref_anchor_point;
	Grammar*		grammarRef;
	Model*			modelRef;
	bool			no_input, uninterpreted, verbal;

	Container*		parent;
	vector<DerivedFrom*>	derivedFrom;
};

#endif /* INTERPRETATION_H_ */
