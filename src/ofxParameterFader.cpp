//
//  ParameterFade.cpp
//  ofStereo2016
//
//  Created by Johan Bichel Lindegaard on 2/25/16.
//

#include "ofxParameterFader.hpp"

void ofxParameterFader::update() {
    
    //cout<<"updating: "<< parameterFades.size() << " fades"<<endl;
    
    for(auto fade : parameterFades) {
        //todo pop from list and delete when done
        //if(fade->hasEnded) delete fade;
        
        fade->update(ofGetElapsedTimef());
    }
    
    vector<AbstractParameterFade *>::iterator it;
    for(it=parameterFades.begin();it!=parameterFades.end();){
        if(!(*it)->isAlive) {
            delete (*it);
            it = parameterFades.erase(it);
        } else {
            ++it;
        }
    }
}

bool ofxParameterFader::isFadingParameter(const ofAbstractParameter & p) {
    for(auto fade : parameterFades) {
        if(fade->p == &p) {
            return true;
        }
    }
    return false;
}

void ofxParameterFader::add(AbstractParameterFade * newFade) {
        
    for(auto & fade : parameterFades) {
            if(fade->p == newFade->p) {
                // Components interrupt all
                if (fade->c == newFade->c || newFade->c == "all" || fade->c == "all") {
                    fade->isAlive = false;
                }
            }
    }
    
    parameterFades.push_back(newFade);
}

bool ofxParameterFader::hasEaseFunction(string easeFunctionName) {
    return (EaseFunctions.find(easeFunctionName) != EaseFunctions.end());
}

ofxeasing::function ofxParameterFader::getEaseFunction(string easeFunctionName) {
    
    if(hasEaseFunction(easeFunctionName)) {
       return EaseFunctions.find(easeFunctionName)->second;
    } else {
        ofLogWarning()<<"easeFunction not found for: '"<<easeFunctionName<<endl;
        return NULL;
    }
}


template<>
void ParameterFade<float>::updateValue(float t) {
    
    float value = getCurrentValue();
    
    if(value != lastValue ) {
        isAlive = false;
    } else {
    
    value = ofxeasing::map_clamp(t, startTime, endTime, fromValue, toValue, easeFn);
    
    lastValue = value;
    p->cast<float>() = value;
    
    }
};

template<>
void ParameterFade<int>::updateValue(float t) {
    
    int value = getCurrentValue();
    
    if(value != lastValue ) {
        isAlive = false;
    } else {
    
        value = ofxeasing::map_clamp(t, startTime, endTime, fromValue, toValue, easeFn);
    
        lastValue = value;
        p->cast<int>() = value;
    
    }
};

template<>
void ParameterFade<double>::updateValue(float t) {
    
    double value = getCurrentValue();
    
    if(value != lastValue ) {
        isAlive = false;
    } else {
    
        value = ofxeasing::map_clamp(t, startTime, endTime, fromValue, toValue, easeFn);
    
        lastValue = value;
        p->cast<double>() = value;
    
    }
};





template<>
void ParameterFade<ofColor>::updateValue(float t) {
    
    ofColor val = getCurrentValue();
    
    if( (val  != lastValue    && c == "all") ||
       (val.r != lastValue.r  && c == "r")   ||
       (val.g != lastValue.g  && c == "g")   ||
       (val.b != lastValue.b  && c == "b")   ||
       (val.a != lastValue.a  && c == "a") )
    {
        isAlive = false;
    } else {
    
    if(c == "all" || c == "r") {
        val.r = ofxeasing::map_clamp(t, startTime, endTime, fromValue.r, toValue.r, easeFn);
    }
    
    if(c == "all" || c == "g") {
        val.g = ofxeasing::map_clamp(t, startTime, endTime, fromValue.g, toValue.g, easeFn);
    }
    
    if(c == "all" || c == "b") {
        val.b = ofxeasing::map_clamp(t, startTime, endTime, fromValue.b, toValue.b, easeFn);
    }
    
    if(c == "all" || c == "a") {
        val.a = ofxeasing::map_clamp(t, startTime, endTime, fromValue.a, toValue.a, easeFn);
    }
    
    lastValue = val;
    p->cast<ofColor>() = val;
    }
}

template<>
void ParameterFade<ofFloatColor>::updateValue(float t) {
    
    ofFloatColor val = getCurrentValue();
    
    if( (val  != lastValue    && c == "all") ||
       (val.r != lastValue.r  && c == "r")   ||
       (val.g != lastValue.g  && c == "g")   ||
       (val.b != lastValue.b  && c == "b")   ||
       (val.a != lastValue.a  && c == "a") )
    {
        isAlive = false;
    } else {
        
        if(c == "all" || c == "r") {
            val.r = ofxeasing::map_clamp(t, startTime, endTime, fromValue.r, toValue.r, easeFn);
        }
        
        if(c == "all" || c == "g") {
            val.g = ofxeasing::map_clamp(t, startTime, endTime, fromValue.g, toValue.g, easeFn);
        }
        
        if(c == "all" || c == "b") {
            val.b = ofxeasing::map_clamp(t, startTime, endTime, fromValue.b, toValue.b, easeFn);
        }
        
        if(c == "all" || c == "a") {
            val.a = ofxeasing::map_clamp(t, startTime, endTime, fromValue.a, toValue.a, easeFn);
        }
        
        lastValue = val;
        p->cast<ofFloatColor>() = val;
    }
}

template<>
void ParameterFade<ofVec3f>::updateValue(float t) {
    
    ofVec3f val = getCurrentValue();
    
    if( (val   != lastValue    && c == "all") ||
       (val.x != lastValue.x  && c == "x")   ||
       (val.y != lastValue.y  && c == "y")   ||
       (val.z != lastValue.z  && c == "z") )
    {
        isAlive = false;
    } else {
    
        if(c == "all" || c == "x") {
            val.x = ofxeasing::map_clamp(t, startTime, endTime, fromValue.x, toValue.x, easeFn);
        }
        if(c == "all" || c == "y") {
            val.y = ofxeasing::map_clamp(t, startTime, endTime, fromValue.y, toValue.y, easeFn);
        }
        if(c == "all" || c == "z") {
            val.z = ofxeasing::map_clamp(t, startTime, endTime, fromValue.z, toValue.z, easeFn);
        }
    
        lastValue = val;
        p->cast<ofVec3f>() = val;
    
    }

}

template<>
void ParameterFade<ofVec2f>::updateValue(float t) {
    
    ofVec2f val = getCurrentValue();
    
    if( (val   != lastValue    && c == "all") ||
       (val.x != lastValue.x  && c == "x")   ||
       (val.y != lastValue.y  && c == "y") )
    { isAlive = false; }
    
    if(c == "all" || c == "x") {
        val.x = ofxeasing::map_clamp(t, startTime, endTime, fromValue.x, toValue.x, easeFn);
    }
    if(c == "all" || c == "y") {
        val.y = ofxeasing::map_clamp(t, startTime, endTime, fromValue.y, toValue.y, easeFn);
    }
    
    lastValue = val;
    p->cast<ofVec2f>() = val;
    
}

void ofxParameterFader::parseOscMessageForParameterGroup(ofxOscMessage & msg, ofAbstractParameter * _p) {
    
    ofAbstractParameter * p = _p;
    cout<<"Received "<<msg.getAddress()<<endl;
    vector<string> address = ofSplitString(msg.getAddress(),"/",true);
    // fade
    
    // get fade method that takes the number of expected arguments before the keyword
    // 1 for sliders
    
    bool fadeValue = false;
    float fadeTime = 2.0; // optional fade time
    ofxeasing::function easeFn = ofxeasing::linear::easeIn;
    // add optional fade ease function - default linear
    // optional wait param
    
    // loop through all arguments
    // if string f - next argument is time if its a float
    // if string e - next argument matches a lookup for easing functions if its an int
    // if string from - next argument is the value to start the fade from
    
    for(int i=0; i<msg.getNumArgs(); i++) {
        cout<<msg.getArgAsString(i)<<endl;
        
        if(msg.getArgType(i) == OFXOSC_TYPE_STRING) {
            if(msg.getArgAsString(i) == "fade") {
                fadeValue = true;
                if(msg.getNumArgs() > i+1) {
                    if(msg.getArgType(i+1) == OFXOSC_TYPE_FLOAT) {
                        fadeTime = msg.getArgAsFloat(i+1);
                    } else if( msg.getArgType(i+1) == OFXOSC_TYPE_INT32) {
                        fadeTime = msg.getArgAsInt(i+1);
                    }
                }
            } else if (hasEaseFunction(msg.getArgAsString(i))){
                //cout<<msg.getArgAsString(i)<<endl;
                easeFn = getEaseFunction(msg.getArgAsString(i));
            }
        }
    }
    
    for(unsigned int i=0;i<address.size();i++){
        
        if(p) {
            if(address[i]==p->getEscapedName()){
                
                if(p->type()==typeid(ofParameterGroup).name()){
                    if(address.size()>=i+1){
                        p = &static_cast<ofParameterGroup*>(p)->get(address[i+1]);
                        
                    }
                }else if(p->type()==typeid(ofParameter<int>).name() && msg.getArgType(0)==OFXOSC_TYPE_INT32){
                    
                    if(fadeValue) {
                        add(new ParameterFade<int>(p, msg.getArgAsInt32(0), fadeTime, easeFn));
                    } else {
                        p->cast<int>() = msg.getArgAsInt32(0);
                    }
                    
                }else if(p->type()==typeid(ofParameter<float>).name() && msg.getArgType(0)==OFXOSC_TYPE_FLOAT){
                    if(fadeValue) {
                        add(new ParameterFade<float>(p, msg.getArgAsFloat(0), fadeTime, easeFn));
                    } else {
                        p->cast<float>() = msg.getArgAsFloat(0);
                    }
                    
                }else if(p->type()==typeid(ofParameter<double>).name() && msg.getArgType(0)==OFXOSC_TYPE_DOUBLE){
                    if(fadeValue) {
                        add(new ParameterFade<double>(p, msg.getArgAsDouble(0), fadeTime, easeFn));
                    } else {
                        p->cast<double>() = msg.getArgAsDouble(0);
                    }
                    
                }else if(p->type()==typeid(ofParameter<bool>).name() && (msg.getArgType(0)==OFXOSC_TYPE_TRUE
                                                                         || msg.getArgType(0)==OFXOSC_TYPE_FALSE
                                                                         || msg.getArgType(0)==OFXOSC_TYPE_INT32
                                                                         || msg.getArgType(0)==OFXOSC_TYPE_INT64
                                                                         || msg.getArgType(0)==OFXOSC_TYPE_FLOAT
                                                                         || msg.getArgType(0)==OFXOSC_TYPE_DOUBLE
                                                                         || msg.getArgType(0)==OFXOSC_TYPE_STRING
                                                                         || msg.getArgType(0)==OFXOSC_TYPE_SYMBOL)){
                    
                    // Bool doesn't fade
                    p->cast<bool>() = msg.getArgAsBool(0);
                    
                } else if(p->type()==typeid(ofParameter<ofColor>).name() &&
                          msg.getArgType(0)!=OFXOSC_TYPE_STRING ) {
                    
                    ofColor col = p->cast<ofColor>();
                    float val = msg.getArgAsFloat(0);
                    
                    // size check
                    string suf = address.back();
                    
                    if(suf == "r") {
                        col.r = val;
                    } else if(suf == "g") {
                        col.g = val;
                    } else if(suf == "b") {
                        col.b = val;
                    } else if(suf == "a") {
                        col.a = val;
                    }
                    
                    if(fadeValue) {
                        add(new ParameterFade<ofColor>(p, col, fadeTime, easeFn, suf));
                    } else {
                        p->cast<ofColor>().set(col);
                    }
                    break;
                    
                } else if(p->type()==typeid(ofParameter<ofFloatColor>).name() &&
                          msg.getArgType(0)!=OFXOSC_TYPE_STRING ) {
                    
                    ofFloatColor col = p->cast<ofFloatColor>();
                    float val = msg.getArgAsFloat(0);
                    
                    // size check
                    string suf = address.back();
                    
                    if(suf == "r") {
                        col.r = val;
                    } else if(suf == "g") {
                        col.g = val;
                    } else if(suf == "b") {
                        col.b = val;
                    } else if(suf == "a") {
                        col.a = val;
                    }
                    
                    if(fadeValue) {
                        add(new ParameterFade<ofFloatColor>(p, col, fadeTime, easeFn, suf));
                    } else {
                        p->cast<ofFloatColor>().set(col);
                    }
                    break;
                    
                    
                } else if(p->type()==typeid(ofParameter<ofVec3f>).name() &&
                          msg.getArgType(0)!=OFXOSC_TYPE_STRING ) {
                    
                    ofVec3f vec = p->cast<ofVec3f>();
                    float val = msg.getArgAsFloat(0);
                    
                    // size check
                    string suf = address.back();
                    
                    // TODO: first time with a suffix all others are set to null, when loaded from file. when all set via osc, suf retains others. maybe loading from file fails to set a certain state?
                    
                    if(suf == "x") {
                        vec.x = val;
                    } else if(suf == "y") {
                        vec.y = val;
                    } else if(suf == "z") {
                        vec.z = val;
                    }
                    
                    if(fadeValue) {
                        add(new ParameterFade<ofVec3f>(p, vec, fadeTime, easeFn, suf));
                    } else {
                        p->cast<ofVec3f>().set(vec);
                    }
                    break;
                    
                } else if(p->type()==typeid(ofParameter<ofVec2f>).name() &&
                          msg.getArgType(0)!=OFXOSC_TYPE_STRING ) {
                    
                    ofVec2f vec = p->cast<ofVec2f>();
                    float val = msg.getArgAsFloat(0);
                    
                    // size check
                    string suf = address.back();
                    
                    if(suf == "x") {
                        vec.x = val;
                    } else if(suf == "y") {
                        vec.y = val;
                    }
                    
                    if(fadeValue) {
                        add(new ParameterFade<ofVec2f>(p, vec, fadeTime, easeFn, suf));
                    } else {
                        p->cast<ofVec2f>().set(vec);
                    }
                    break;
                    
                    
                    
                } else if(msg.getArgType(0)==OFXOSC_TYPE_STRING){
                    
                    if(fadeValue) {
                        
                        if(p->type()==typeid(ofParameter<ofColor>).name()) {
                            
                            ofParameter<ofColor> target;
                            target.fromString(msg.getArgAsString(0));
                            add(new ParameterFade<ofColor>(p, target.get(), fadeTime, easeFn));
                            
                        } else if(p->type()==typeid(ofParameter<ofFloatColor>).name()) {
                            
                            ofParameter<ofFloatColor> target;
                            target.fromString(msg.getArgAsString(0));
                            add(new ParameterFade<ofFloatColor>(p, target.get(), fadeTime, easeFn));
                            
                        } else if(p->type()==typeid(ofParameter<ofVec3f>).name()) {
                            
                            ofParameter<ofVec3f> target;
                            target.fromString(msg.getArgAsString(0));
                            add(new ParameterFade<ofVec3f>(p, target.get(), fadeTime, easeFn));
                            
                        } else if(p->type()==typeid(ofParameter<ofVec2f>).name()) {
                            
                            ofParameter<ofVec2f> target;
                            target.fromString(msg.getArgAsString(0));
                            add(new ParameterFade<ofVec2f>(p, target.get(), fadeTime, easeFn));
                        }
                        
                        // Qlab will pass arguments as strings, if there's a following fade string, therefore we catch floats, ints and doubles here as well
                        
                        else if(p->type()==typeid(ofParameter<float>).name()) {
                            
                            ofParameter<float> target;
                            target.fromString(msg.getArgAsString(0));
                            add(new ParameterFade<float>(p, target.get(), fadeTime, easeFn));
                            
                        } else if(p->type()==typeid(ofParameter<double>).name()) {
                            
                            ofParameter<double> target;
                            target.fromString(msg.getArgAsString(0));
                            add(new ParameterFade<double>(p, target.get(), fadeTime, easeFn));
                            
                        } else if(p->type()==typeid(ofParameter<int>).name()) {
                            
                            ofParameter<int> target;
                            target.fromString(msg.getArgAsString(0));
                            add(new ParameterFade<int>(p, target.get(), fadeTime, easeFn));
                        }
                        
                        
                    } else {
                        p->fromString(msg.getArgAsString(0));
                    }
                    
                }
            }
        }
    }
}


using namespace ofxeasing;

// easing lookup from http://easings.net/
const std::map<string, ofxeasing::function> ofxParameterFader::EaseFunctions {
    {"linear",           linear::easeIn},
    
    {"easeInSine",       sine::easeIn},
    {"easeOutSine",      sine::easeIn},
    {"easeInOutSine",    sine::easeIn},
    
    {"easeInQuad",       quad::easeIn},
    {"easeOutQuad",      quad::easeOut},
    {"easeInOutQuad",    quad::easeInOut},
    
    {"easeInCubic",      cubic::easeIn},
    {"easeOutCubic",     cubic::easeOut},
    {"easeInOutCubic",   cubic::easeInOut},
    
    {"easeInQuart",      quart::easeIn},
    {"easeOutQuart",     quart::easeOut},
    {"easeInOutQuart",   quart::easeInOut},
    
    {"easeInQuint",      quint::easeIn},
    {"easeOutQuint",     quint::easeOut},
    {"easeInOutQuint",   quint::easeInOut},
    
    {"easeInExpo",       exp::easeIn},
    {"easeOutExpo",      exp::easeOut},
    {"easeInOutExpo",    exp::easeInOut},
    
    {"easeInCirc",       circ::easeIn},
    {"easeOutCirc",      circ::easeOut},
    {"easeInOutCirc",    circ::easeInOut},
    
    {"easeInBack",       back::easeIn},
    {"easeOutBack",      back::easeOut},
    {"easeInOutBack",    back::easeInOut},
    
    {"easeInElastic",    elastic::easeIn},
    {"easeOutElastic",   elastic::easeOut},
    {"easeInOutElastic", elastic::easeInOut},
    
    {"easeInBounce",     bounce::easeIn},
    {"easeOutBounce",    bounce::easeOut},
    {"easeInOutBounce",  bounce::easeInOut},
};
